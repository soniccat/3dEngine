//
//  ES1Renderer.m
//  sample
//
//  Created by alexey on 1/4/10.
//  Copyright __MyCompanyName__ 2010. All rights reserved.
//

#import "ES1Renderer.h"
#import "SEMain.h"

#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) / 180.0 * 3.14f)
#include <cmath>

SETexturePtr objectTexture;
GLuint depthRenderbuffer;

#define USE_DEPTH_BUFFER 1

SEPhysicObjectPtr physicObject1;
SEPhysicObjectPtr physicObject2;

@implementation ES1Renderer

// Create an ES 1.1 context
- (id) init
{
	if (self = [super init])
	{        
		context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        
        if (!context || ![EAGLContext setCurrentContext:context])
		{
            [self release];
            return nil;
        }
		
		// Create default framebuffer object. The backing will be allocated for the current layer in -resizeFromLayer
		/*glGenFramebuffersOES(1, &defaultFramebuffer);
		glGenRenderbuffersOES(1, &colorRenderbuffer);
		glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
		glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
		glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, colorRenderbuffer);
		*/
		
		glViewport(0, 0, 320, 480);
		
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		
		const GLfloat zNear = 0.1; 
		GLfloat zFar = 100.0;
		GLfloat fieldOfView = 60.0; 
		GLfloat size; 
		GLfloat window_width = 320;
		GLfloat window_height = 480;
		
		glEnable(GL_DEPTH_TEST); 
		size = zNear * tanf(DEGREES_TO_RADIANS(fieldOfView) / 2.0); 
		glFrustumf(-size, size, -size / (window_width / window_height), size / (window_width / window_height), zNear, zFar);
		glMatrixMode(GL_MODELVIEW);
		
		//glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		// Enable blending
		//glEnable(GL_BLEND);
		
		SELoadDefaultOpenGLSettings();
		
		btCollisionConfigurationPtr collisionConfiguration	= btCollisionConfigurationPtr( SENewObject<btDefaultCollisionConfiguration>() );
		btDispatcherPtr				dispatcher				= btDispatcherPtr ( SENewObject<btCollisionDispatcher>(collisionConfiguration.get()) );
		btBroadphaseInterfacePtr	overlappingPairCache	= btBroadphaseInterfacePtr( SENewObject<btDbvtBroadphase>() );
		btConstraintSolverPtr		solver					= btConstraintSolverPtr( SENewObject<btSequentialImpulseConstraintSolver>() );
		
		SEPhysicWorld::sharedInstance()->InitDiscreteDynamicsWorld( dispatcher ,overlappingPairCache, solver, collisionConfiguration );
		SEPhysicWorld::sharedInstance()->world()->setGravity(btVector3(0,-10,0));
		
		
		SEPath currentPath;
		SEPath::CurrentDirectory(&currentPath);
		currentPath.AppendName("objects");
		
		SESceneLoader loader;
		loader.Load( &currentPath );
		
		
		//add physic objects
		
		///create a few basic rigid bodies
		btCollisionShapePtr boxShape = btCollisionShapePtr( SENewObject<btBoxShape>(btVector3(btScalar(1.0),btScalar(1.0),btScalar(1.0))) );
		
		
		btTransform groundTransform;
		groundTransform.setIdentity();
		groundTransform.setOrigin(btVector3(0,0,0));
		
		{
			btScalar mass(0.0);
			
			//rigidbody is dynamic if and only if mass is non zero, otherwise static
			bool isDynamic = (mass != 0.f);
			
			btVector3 localInertia(0,0,0);
			if (isDynamic)
				boxShape->calculateLocalInertia(mass,localInertia);
			
			//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
			//btDefaultMotionState* myMotionState = SENewObject<btDefaultMotionState>(groundTransform);
			//btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
			//btRigidBody* body = new btRigidBody(rbInfo);
			
			SEMeshPtr mesh = SEObjectStore::sharedInstance()->GetMesh( "Plane" );
			
			btDefaultMotionStatePtr myMotionState = btDefaultMotionStatePtr( SENewObject<btDefaultMotionState>(groundTransform) );
			
			physicObject1 = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
			physicObject1->Init( mass, mesh, myMotionState, boxShape, localInertia  );
			
			SEPhysicWorld::sharedInstance()->AddObject( physicObject1 );
		}
		
		groundTransform.setOrigin(btVector3(0.0,8,1.5));
		
		{
			btScalar mass(0.1);
			
			//rigidbody is dynamic if and only if mass is non zero, otherwise static
			bool isDynamic = (mass != 0.f);
			
			btVector3 localInertia(0,0,0);
			if (isDynamic)
				boxShape->calculateLocalInertia(mass,localInertia);
			
			//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
			//btDefaultMotionState* myMotionState = SENewObject<btDefaultMotionState>(groundTransform);
			//btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,groundShape,localInertia);
			
			SEMeshPtr mesh = SEObjectStore::sharedInstance()->GetMesh( "Plane" );
			
			btDefaultMotionStatePtr myMotionState = btDefaultMotionStatePtr( SENewObject<btDefaultMotionState>(groundTransform) );
			
			physicObject2 = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
			physicObject2->Init( mass, mesh, myMotionState, boxShape, localInertia  );
			
			SEPhysicWorld::sharedInstance()->AddObject( physicObject2 );
		}
		
		//SEImageLoader imageLoader;
		//SEImagePtr image = imageLoader.Load("test.jpg");
		
		//objectTexture = SETexturePtr( new SETexture );
		//objectTexture->Init( image );
		//objectTexture->Use();
		
		BREAKPOINTPLACE;
	}
	
	return self;
}

- (void) render
{
    // Replace the implementation of this method to do your own custom drawing
    
    static const GLfloat squareVertices[] = {
        -0.5f,  -0.33f,
         0.5f,  -0.33f,
        -0.5f,   0.33f,
         0.5f,   0.33f,
    };
	
    static const GLubyte squareColors[] = {
        255, 255,   0, 255,
        0,   255, 255, 255,
        0,     0,   0,   0,
        255,   0, 255, 255,
    };
    
	static float transY = 0.0f;
	
	// This application only creates a single context which is already set current at this point.
	// This call is redundant, but needed if dealing with multiple contexts.
    [EAGLContext setCurrentContext:context];
    
	// This application only creates a single default framebuffer which is already bound at this point.
	// This call is redundant, but needed if dealing with multiple framebuffers.
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
    
	glLoadIdentity();
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	//static float angle = 0;
	//angle += 0.1f;
	
	SEPhysicWorld::sharedInstance()->world()->stepSimulation(1.f/60.f,10);
	
	glTranslatef(0,0,-10);
	//glRotatef(angle,1,1,0);
	
	//SEMeshPtr mesh = SEObjectStore::sharedInstance()->GetMesh("Plane");
	//mesh->Draw();
	
	if( physicObject1.get() )
		physicObject1->Draw();
	
	if( physicObject2.get() )
		physicObject2->Draw();
	
	
	//glRotatef(-angle,1,1,0);
	glTranslatef(0,0,10);
	
	/*
	glTranslatef(0.0f, (GLfloat)(sinf(transY)/2.0f), 0.0f);
	transY += 0.075f;
    
    glVertexPointer(2, GL_FLOAT, 0, squareVertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
    glEnableClientState(GL_COLOR_ARRAY);
    
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	*/
    
	// This application only creates a single color renderbuffer which is already bound at this point.
	// This call is redundant, but needed if dealing with multiple renderbuffers.
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
    [context presentRenderbuffer:GL_RENDERBUFFER_OES];
}

- (BOOL)createFramebuffer:(CAEAGLLayer *)layer
{
    glGenFramebuffersOES(1, &defaultFramebuffer);
    glGenRenderbuffersOES(1, &colorRenderbuffer);
    
    glBindFramebufferOES(GL_FRAMEBUFFER_OES, defaultFramebuffer);
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:layer];
    glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_COLOR_ATTACHMENT0_OES, GL_RENDERBUFFER_OES, colorRenderbuffer);
    
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
    
    if (USE_DEPTH_BUFFER) {
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
    }
    
    if(glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES) {
        NSLog(@"failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
    
    return YES;
}


- (BOOL) resizeFromLayer:(CAEAGLLayer *)layer
{	
	return [self createFramebuffer:layer];
/*
	// Allocate color buffer backing based on the current layer size
    glBindRenderbufferOES(GL_RENDERBUFFER_OES, colorRenderbuffer);
    [context renderbufferStorage:GL_RENDERBUFFER_OES fromDrawable:layer];
	glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_WIDTH_OES, &backingWidth);
    glGetRenderbufferParameterivOES(GL_RENDERBUFFER_OES, GL_RENDERBUFFER_HEIGHT_OES, &backingHeight);
	
	if (USE_DEPTH_BUFFER) {
        glGenRenderbuffersOES(1, &depthRenderbuffer);
        glBindRenderbufferOES(GL_RENDERBUFFER_OES, depthRenderbuffer);
        glRenderbufferStorageOES(GL_RENDERBUFFER_OES, GL_DEPTH_COMPONENT16_OES, backingWidth, backingHeight);
        glFramebufferRenderbufferOES(GL_FRAMEBUFFER_OES, GL_DEPTH_ATTACHMENT_OES, GL_RENDERBUFFER_OES, depthRenderbuffer);
    }
	
    if (glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES) != GL_FRAMEBUFFER_COMPLETE_OES)
	{
		NSLog(@"Failed to make complete framebuffer object %x", glCheckFramebufferStatusOES(GL_FRAMEBUFFER_OES));
        return NO;
    }
    
    return YES;
 */
}

- (void) dealloc
{
	// Tear down GL
	if (defaultFramebuffer)
	{
		glDeleteFramebuffersOES(1, &defaultFramebuffer);
		defaultFramebuffer = 0;
	}

	if (colorRenderbuffer)
	{
		glDeleteRenderbuffersOES(1, &colorRenderbuffer);
		colorRenderbuffer = 0;
	}
	
	// Tear down context
	if ([EAGLContext currentContext] == context)
        [EAGLContext setCurrentContext:nil];
	
	if(depthRenderbuffer) 
	{
        glDeleteRenderbuffersOES(1, &depthRenderbuffer);
        depthRenderbuffer = 0;
    }
	
	[context release];
	context = nil;
	
	[super dealloc];
}

@end
