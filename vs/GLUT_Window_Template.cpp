//*************************************************************************
//
//  File Name	: GLUT Window Template
//  Author		: Ali BaderEddin
//  Date		: December 2003
//  
//  Description	: Openning an OpenGL window using GLUT library...
//  
//*************************************************************************

#include "SEMain.h"
#include "SESceneLoader.h"
#include <vector>

#include "btBulletDynamicsCommon.h"
/*
btDefaultCollisionConfiguration* collisionConfiguration;
btCollisionDispatcher* dispatcher;
btBroadphaseInterface* overlappingPairCache;
btSequentialImpulseConstraintSolver* solver;
btDiscreteDynamicsWorld* dynamicsWorld;
*/


using namespace std;

//  Include GLUT, OpenGL, and GLU libraries
#include <gl/glut.h>

//  Standard Input\Output C Library
#include <stdio.h>

#define DEGREES_TO_RADIANS(__ANGLE__) ((__ANGLE__) / 180.0 * 3.14f)
#include <cmath>

//  Initialization
void init ();

//  Callback functions
void display (void);
void reshape (int w, int h);
void mouse (int button, int state, int x, int y);
void motion (int x, int y);
void pmotion (int x, int y);
void keyboard (unsigned char key, int x, int y);
void special (int key, int x, int y);

//  Support Functions
void centerOnScreen ();
void drawObject ();

//  define the window position on screen
int window_x;
int window_y;

//  variables representing the window size
int window_width = 240;
int window_height = 240;

//  variable representing the window title
sechar *window_title = "GLUT Window Template";

//  Tells whether to display the window full screen or not
//  Press Alt + Esc to exit a full screen.
int full_screen = 0;


class CameraController: public SETouchControllerDelegate
{
	bool leftButtonPressed;
	bool rightButtonPressed;
	SETouch curTouch;

	btVector3 vec;

public:
	CameraController()
	{
		leftButtonPressed = false;
		rightButtonPressed = false;

		SECameraPtr camera = SEObjectStore::sharedInstance()->GetCamera("Camera");
		camera->SetSeePoint( btVector3(0,0,0) );
		
		const btVector3& position = camera->position();
		camera->SetPosition( btVector3( 0,position.y(),position.z()) );

		vec = camera->position();
	}

	virtual void TouchesBegin( SETouchArray::iterator touch, size_t count, SETouchButton button )
	{
		//check selected object

		SECameraPtr camera = SEObjectStore::sharedInstance()->GetCamera("Camera");

		btVector3 rayTo = getRayTo( camera, window_width, window_height, touch->x(), touch->y() );

		btVector3 rayFrom;
					/*if (m_ortho)
					{
						rayFrom = rayTo;
						rayFrom.setZ(-100.f);
					} else*/
					{
						rayFrom = camera->position();
					}
					
					btCollisionWorld::ClosestRayResultCallback rayCallback(rayFrom,rayTo);
					SEPhysicWorld::sharedInstance()->world()->rayTest(rayFrom,rayTo,rayCallback);
					if (rayCallback.hasHit())
					{


						btRigidBody* body = btRigidBody::upcast(rayCallback.m_collisionObject);

						if (body)
						{
							printf( "up up %p ,%d\n", body, rand()%1000 ); 
						}
					}




		if(button == SETouchButtonLeft)
			leftButtonPressed = true;

		if(button == SETouchButtonRight)
			rightButtonPressed = true;

		curTouch = *touch;
	}

	virtual void TouchesMove( SETouchArray::iterator touch, size_t count, SETouchButton button )
	{
		SECameraPtr camera = SEObjectStore::sharedInstance()->GetCamera("Camera");

		if(rightButtonPressed)
		{	
			const btVector3& seeVector = camera->seePoint();
			const btVector3& position = camera->position();

			printf( "position pt %f %f %f\n", position.x(), position.y(), position.z() );

			static float dx12 = position.x() - seeVector.x();
			static float dy12 = position.y() - seeVector.y();
			static float dz12 = position.z() - seeVector.z();

			float dx = touch->x() - curTouch.x();
			float dy = touch->y() - curTouch.y();

			static float axz = 0; 
			static float ayz = 0; 

			//axz -= dx / 100.0f;
			//ayz -= dy / 100.0f;

			static float a1 = 0;
			static float a2 = 0;

			a1 += dy / 100.0f; 
			a2 -= dx / 100.0f;

			/*btQuaternion quat(0,1,0,0.1f);
			btQuaternion q2 = vec * quat;

			btVector3 v( q2.getX()/q2.getW(), q2.getY()/q2.getW(), q2.getZ()/q2.getW());
*/

			btQuaternion q1 = btQuaternion(btVector3(1.0, 0.0, 0.0), a1);
			btQuaternion q2 = btQuaternion(btVector3(0.0, 1.0, 0.0), a2);

			btQuaternion q3 = q2 * q1;

			btTransform tr(q3);
			btVector3 drawVec = tr(vec);

			camera->SetPosition( drawVec );
/*
			btMatrix3x3 matrix1( 1,0,0,
				0,cos(a1),-sin(a1),
				0,sin(a1),cos(a1));

			btMatrix3x3 matrix2( cos (a2),0,sin (a2),
				0,1,0,
				-sin(a2),0,cos(a2));

			//btMatrix3x3 matrix2( cos(angle),-sin (angle), 0,
			//	sin(angle),cos(angle),0,
			//	0,0,1);

			btMatrix3x3 matrix = matrix1 * matrix2;

			btVector3 drawVec = vec * matrix;

			camera->SetPosition( btVector3( drawVec.x(), drawVec.y(), drawVec.z() ) );
*/
		}

		curTouch = *touch;
	}

	virtual void TouchesEnd( SETouchArray::iterator touch, size_t count, SETouchButton button )
	{
		if(button == SETouchButtonLeft)
			leftButtonPressed = false;

		if(button == SETouchButtonRight)
			rightButtonPressed = false;
	}
};

typedef shared_ptr<CameraController> CameraControllerPtr;


//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init ()
{	
	//  Set the frame buffer clear color to black. 
	glClearColor (0.5, 0.5, 0.5, 1.0);
	
	SELoadDefaultOpenGLSettings();
}

//-------------------------------------------------------------------------
//  This function is passed to glutDisplayFunc in order to display 
//	OpenGL contents on the window.
//-------------------------------------------------------------------------

SEPhysicObjectPtr physicObject1;
SEPhysicObjectPtr physicObject2;


void display (void)
{
	SEGLAssert;

	//  Clear the window or more specifically the frame buffer...
	//  This happens by replacing all the contents of the frame
	//  buffer by the clear color (black in our case)
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//static float z = -1;
	//z += 0.1f;


	glLoadIdentity();

	SECameraPtr camera = SEObjectStore::sharedInstance()->GetCamera("Camera");
	camera->Use();

	//glTranslatef(0,0,-10);
	//glRotatef(30,1,1,0);


	//for (int i=0;i<150;i++)
	//{
		SEPhysicWorld::sharedInstance()->world()->stepSimulation(1.f/60.f,10);
		
		//print positions of all objects
		/*for (int j= SEPhysicWorld::sharedInstance()->world()->getNumCollisionObjects()-1; j>=0 ;j--)
		{
			btCollisionObject* obj = SEPhysicWorld::sharedInstance()->world()->getCollisionObjectArray()[j];
			btRigidBody* body = btRigidBody::upcast(obj);
			if (body && body->getMotionState())
			{
				btTransform trans;
				body->getMotionState()->getWorldTransform(trans);
				
				if( j == 0 )
				{
					glTranslatef( trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() );
					drawObject();
					glTranslatef(-trans.getOrigin().getX(),-trans.getOrigin().getY(),-trans.getOrigin().getZ() );

				}else if( j == 1 )
				{
					glTranslatef( trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() );
					
					btQuaternion quatern = trans.getRotation();
					btVector3 vec = quatern.getAxis();

					float radToGrad = 180.0/3.14;

					//printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
					printf("world rot = %f,%f,%f,%f\n",quatern.getAngle(),vec.x(), vec.y(), vec.z());


					glRotatef( quatern.getAngle()*radToGrad, vec.x(), vec.y(), vec.z() );
					drawObject();
					glRotatef( -quatern.getAngle()*radToGrad, vec.x(), vec.y(), vec.z() );

					glTranslatef(-trans.getOrigin().getX(),-trans.getOrigin().getY(),-trans.getOrigin().getZ() );
				}
			}
		}*/
	//}

	//  Draw object

		if( physicObject1.get() )
			physicObject1->Draw();

		if( physicObject2.get() )
			physicObject2->Draw();
	

	//glRotatef(-30,1,1,0);
	//glTranslatef(0,0,10);

	//  Swap contents of backward and forward frame buffers
	glutSwapBuffers ();
	glFlush();
	glutPostRedisplay();
}

//-------------------------------------------------------------------------
//  Draws our object.
//-------------------------------------------------------------------------
void drawObject ()
{
	//  Show when are displaying an object
	//printf ("Displaying object...\n");
	
	//  Draw Icosahedron
	//glutWireIcosahedron ();

	//SEMeshPtr mesh = SEObjectStore::sharedInstance()->GetMesh( "Plane" );

	//static GLUquadric* quadr = gluNewQuadric();

	//gluLookAt (0.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.1, 0.0);

	//static float angle = 0;
	//angle += 0.1f;
	

	//static float z = -1;
	//z += -0.01f;

	
	//glRotatef(angle,1,1,0);
	//gluSphere( quadr,5,10,10 );
	
	//mesh->Draw();

	//glRotatef(-angle,1,1,0);
}

//-------------------------------------------------------------------------
//  This function is passed to the glutReshapeFunc and is called 
//  whenever the window is resized.
//-------------------------------------------------------------------------
void reshape (int w, int h)
{
	//  Stay updated with the window width and height
	window_width = w;
	window_height = h;

	//  Reset viewport
	glViewport(0, 0, window_width, window_height);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();

	
	btScalar aspect;
	btVector3 extents;

	if (window_width > window_height) 
	{
		aspect = window_width / (btScalar)window_height;
		extents.setValue(aspect * 1.0f, 1.0f,0);
	} else 
	{
		aspect = window_height / (btScalar)window_width;
		extents.setValue(1.0f, aspect*1.f,0);
	}

		if (window_width > window_height) 
		{
			glFrustum (-aspect, aspect, -1.0, 1.0, 1.0, 10000.0);
		} else 
		{
			glFrustum (-1.0, 1.0, -aspect, aspect, 1.0, 10000.0);
		}

		glMatrixMode(GL_MODELVIEW);


	/*
const GLfloat zNear = 0.1; 
GLfloat zFar = 200.0;
GLfloat fieldOfView = 60.0; 
GLfloat size; 

size = zNear * tanf(DEGREES_TO_RADIANS(fieldOfView) / 2.0); 
glFrustum(-size, size, -size / (window_width / window_height), size / (window_width / window_height), zNear, zFar);


	glMatrixMode (GL_MODELVIEW);

	//  Print current width and height on the screen
	printf ("Window Width: %d, Window Height: %d.\n", window_width, window_height);
	*/
}

//-------------------------------------------------------------------------
//  This function is passed to the glutMouseFunc and is called 
//  whenever the mouse is clicked.
//-------------------------------------------------------------------------
void mouse (int button, int state, int x, int y)
{
	switch (button)
	{
		//  Left Button Clicked
		case GLUT_LEFT_BUTTON:

			switch (state)
			{
				//  Pressed 
				case GLUT_DOWN:
					//printf ("Mouse Left Button Pressed (Down)...\n");

					SETouchController::sharedInstance()->BeginTouching();
					SETouchController::sharedInstance()->AddTouch( SETouch( x,y ) );
					SETouchController::sharedInstance()->EndTouching( SETouchBegin, SETouchButtonLeft );
					break;

				//  Released
				case GLUT_UP:
					//printf ("Mouse Left Button Released (Up)...\n");

					SETouchController::sharedInstance()->BeginTouching();
					SETouchController::sharedInstance()->AddTouch( SETouch( x,y ) );
					SETouchController::sharedInstance()->EndTouching( SETouchEnd, SETouchButtonLeft );
					break;
			}

			break;

		//  Middle Button clicked
		case GLUT_MIDDLE_BUTTON:
			
			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					//printf ("Mouse Middle Button Pressed (Down)...\n");

					SETouchController::sharedInstance()->BeginTouching();
					SETouchController::sharedInstance()->AddTouch( SETouch( x,y ) );
					SETouchController::sharedInstance()->EndTouching( SETouchBegin, SETouchButtonMiddle );
					break;
				//  Released
				case GLUT_UP:
					//printf ("Mouse Middle Button Released (Up)...\n");

					SETouchController::sharedInstance()->BeginTouching();
					SETouchController::sharedInstance()->AddTouch( SETouch( x,y ) );
					SETouchController::sharedInstance()->EndTouching( SETouchEnd, SETouchButtonMiddle );
					break;
			}

			break;

		//  Right Button Clicked
		case GLUT_RIGHT_BUTTON:
			
			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					//printf ("Mouse Right Button Pressed (Down)...\n");

					SETouchController::sharedInstance()->BeginTouching();
					SETouchController::sharedInstance()->AddTouch( SETouch( x,y ) );
					SETouchController::sharedInstance()->EndTouching( SETouchBegin, SETouchButtonRight );
					break;
				//  Released

				case GLUT_UP:
					//printf ("Mouse Right Button Released (Up)...\n");

					SETouchController::sharedInstance()->BeginTouching();
					SETouchController::sharedInstance()->AddTouch( SETouch( x,y ) );
					SETouchController::sharedInstance()->EndTouching( SETouchEnd, SETouchButtonRight );
					break;
			}

			break;

	}
}

//-------------------------------------------------------------------------
//  This function is passed to the glutMotionFunc and is called 
//  whenever the mouse is dragged.
//-------------------------------------------------------------------------
void motion (int x, int y)
{
	//  Print the mouse drag position
	//printf ("Mouse Drag Position: %d, %d.\n", x, y);

	SETouchController::sharedInstance()->BeginTouching();
	SETouchController::sharedInstance()->AddTouch( SETouch( x,y ) );
	SETouchController::sharedInstance()->EndTouching( SETouchMove );
}

//-------------------------------------------------------------------------
//  This function is passed to the glutPassiveMotionFunc and is called 
//  whenever the mouse is moved.
//-------------------------------------------------------------------------
void pmotion (int x, int y)
{
	//  Print mouse move positopn
	//printf ("Mouse Move Position: %d, %d.\n", x, y);
}

//-------------------------------------------------------------------------
//  This function is passed to the glutKeyboardFunc and is called 
//  whenever the user hits a key.
//-------------------------------------------------------------------------
void keyboard (unsigned char key, int x, int y)
{
	//  Print what key the user is hitting
	printf ("User is hitting the '%c' key.\n", key);
	printf ("ASCII code is %d.\n", key);
	
	switch (key)
	{
		//  User hits A key
		case 'a':
			
			break;

		//  User hits Shift + A key
		case 'A':
			
			break;

		//  User hits Enter
		case '\r':
			printf ("User is hitting the Return key.\n"); 
			break;

		//  User hits Space
		case ' ':
			printf ("User is hitting the Space key.\n"); 
			break;

		//  User hits back space
		case 8:
			printf ("User is hitting the Back Space key.\n"); 
			break;

		//  User hits ESC key
		case 27:
			exit (1);
			break;
	}

	glutPostRedisplay ();
}

//-------------------------------------------------------------------------
//  This function is passed to the glutSpecialFunc and is called 
//  whenever the user hits a special key.
//-------------------------------------------------------------------------
void special (int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_F1 :
			printf ("F1 function key.\n"); 
			break;
		case GLUT_KEY_F2 :
			printf ("F2 function key. \n");  
			break;
		case GLUT_KEY_F3 :
			printf ("F3 function key. \n");  
			break;
		case GLUT_KEY_F4 :
			printf ("F4 function key. \n");  
			break;
		case GLUT_KEY_F5 :
			printf ("F5 function key. \n");  
			break;
		case GLUT_KEY_F6 :
			printf ("F6 function key. \n");  
			break;
		case GLUT_KEY_F7 :
			printf ("F7 function key. \n");  
			break;
		case GLUT_KEY_F8 :
			printf ("F8 function key. \n");  
			break;
		case GLUT_KEY_F9 :
			printf ("F9 function key. \n");  
			break;
		case GLUT_KEY_F10 :
			printf ("F10 function key. \n");  
			break;
		case GLUT_KEY_F11 :
			printf ("F11 function key. \n");  
			break;
		case GLUT_KEY_F12 :
			printf ("F12 function key. \n");  
			break;
		case GLUT_KEY_LEFT :
			printf ("Left directional key. \n");  
			break;
		case GLUT_KEY_UP :
			printf ("Up directional key. \n");  
			break;
		case GLUT_KEY_RIGHT :
			printf ("Right directional key. \n");  
			break;
		case GLUT_KEY_DOWN :
			printf ("Down directional key. \n");  
			break;
		case GLUT_KEY_PAGE_UP :
			printf ("Page up directional key. \n");  
			break;
		case GLUT_KEY_PAGE_DOWN :
			printf ("Page down directional key. \n");  
			break;
		case GLUT_KEY_HOME :
			printf ("Home directional key. \n");  
			break;
		case GLUT_KEY_END :
			printf ("End directional key. \n");  
			break;
		case GLUT_KEY_INSERT :
			printf ("Inset directional key. \n");  
			break;
	}
	
	glutPostRedisplay ();
}

//-------------------------------------------------------------------------
//  This function sets the window x and y coordinates
//  such that the window becomes centered
//-------------------------------------------------------------------------
void centerOnScreen ()
{
	window_x = (glutGet (GLUT_SCREEN_WIDTH) - window_width)/2;
	window_y = (glutGet (GLUT_SCREEN_HEIGHT) - window_height)/2;
}


//-------------------------------------------------------------------------
//  Program Main method.
//-------------------------------------------------------------------------
SETexturePtr objectTexture;
CameraControllerPtr cameraController;


void main (int argc, sechar **argv)
{
	//physic world
	btCollisionConfigurationPtr collisionConfiguration	= btCollisionConfigurationPtr( SENewObject<btDefaultCollisionConfiguration>() );
	btDispatcherPtr				dispatcher				= btDispatcherPtr ( SENewObject<btCollisionDispatcher>(collisionConfiguration.get()) );
	btBroadphaseInterfacePtr	overlappingPairCache	= btBroadphaseInterfacePtr( SENewObject<btDbvtBroadphase>() );
	btConstraintSolverPtr		solver					= btConstraintSolverPtr( SENewObject<btSequentialImpulseConstraintSolver>() );

	SEPhysicWorld::sharedInstance()->InitDiscreteDynamicsWorld( dispatcher ,overlappingPairCache, solver, collisionConfiguration );
	SEPhysicWorld::sharedInstance()->world()->setGravity(btVector3(0,-9,0));


	//  Set the window x and y coordinates such that the 
	//  window becomes centered
	centerOnScreen();

	//  Connect to the windowing system + create a window
	//  with the specified dimensions and position
	//  + set the display mode + specify the window title.
	glutInit(&argc, argv);
	glutInitWindowSize (window_width, window_height);
	glutInitWindowPosition (window_x, window_y);

	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutCreateWindow (window_title);

	//  View in full screen if the full_screen flag is on
	if (full_screen)
		glutFullScreen ();

	//  Set OpenGL program initial state.
	init();
	
	// Set the callback functions
	glutDisplayFunc (display);
	glutReshapeFunc  (reshape);
	glutMouseFunc (mouse);
	glutMotionFunc (motion);
	glutPassiveMotionFunc (pmotion);
	glutKeyboardFunc (keyboard);
	glutSpecialFunc (special);


	SEPath currentPath;
	SEPath::CurrentDirectory( &currentPath );
	currentPath.AppendName( "objects" );

	SESceneLoader loader;
	loader.Load( &currentPath );

	//camera
	cameraController = CameraControllerPtr( SENewObject<CameraController>() );
	SETouchController::sharedInstance()->AddDelegate( cameraController );
	
	///create a few basic rigid bodies
	SEMeshPtr planeMesh = SEObjectStore::sharedInstance()->GetMesh( "Plane.001" );
	SEMeshPtr cubeMesh = SEObjectStore::sharedInstance()->GetMesh( "Plane" );

	btTriangleMeshPtr triangleMesh = btTriangleMeshPtr( SENewObject<btTriangleMesh>() );
	planeMesh->GetTriangleMesh( triangleMesh );

	//btTriangleVertexArrayPtr vertexArray = mesh->CreateTriangleIndexVertexArray();

	btCollisionShapePtr boxShape = btCollisionShapePtr( SENewObject<btBoxShape>(btVector3(btScalar(1.0),btScalar(1.0),btScalar(1.0))) );
	btBvhTriangleMeshShapePtr triangleShape = btBvhTriangleMeshShapePtr( SENewObject<btBvhTriangleMeshShape>( triangleMesh.get(), true, true ) );


	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,0,0));
	//groundTransform.setRotation( btQuaternion( -DEGREES_TO_RADIANS(180) ,0, 0,1) );

	{
		btScalar mass(0.0);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			triangleShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionStatePtr myMotionState = btDefaultMotionStatePtr( SENewObject<btDefaultMotionState>(groundTransform) );

		physicObject1 = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
		physicObject1->Init( mass, planeMesh, myMotionState,triangleShape,localInertia );

		SEPhysicWorld::sharedInstance()->AddObject( physicObject1 );
	}

	groundTransform.setOrigin(btVector3(0.0,10,-30.0));
	groundTransform.setRotation( btQuaternion() );

	{
		btScalar mass(0.1);

		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			boxShape->calculateLocalInertia(mass,localInertia);

		btDefaultMotionStatePtr myMotionState = btDefaultMotionStatePtr( SENewObject<btDefaultMotionState>(groundTransform) );

		physicObject2 = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
		physicObject2->Init( mass, cubeMesh, myMotionState, boxShape, localInertia  );

		SEPhysicWorld::sharedInstance()->AddObject( physicObject2 );
	}


	//  Start GLUT event processing loop
	glutMainLoop();
}

