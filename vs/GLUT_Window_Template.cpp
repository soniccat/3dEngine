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

vector<int, SEAllocator<int>> mass;

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

//-------------------------------------------------------------------------
//  Set OpenGL program initial state.
//-------------------------------------------------------------------------
void init ()
{	
	//  Set the frame buffer clear color to black. 
	glClearColor (0.0, 0.0, 0.0, 0.0);
	
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

	glLoadIdentity();
	glTranslatef(0,0,-10);


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
	

	glTranslatef(0,0,10);

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
	//glOrtho(-10,10,10,-10,-10,10);
	//glFrustum (-5.0, 5.0, -5.0, 5.0, 1.5, 200.0);


const GLfloat zNear = 0.1; 
GLfloat zFar = 100.0;
GLfloat fieldOfView = 60.0; 
GLfloat size; 

size = zNear * tanf(DEGREES_TO_RADIANS(fieldOfView) / 2.0); 
glFrustum(-size, size, -size / (window_width / window_height), size / (window_width / window_height), zNear, zFar);


	glMatrixMode (GL_MODELVIEW);

	//  Print current width and height on the screen
	printf ("Window Width: %d, Window Height: %d.\n", window_width, window_height);
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
					printf ("Mouse Left Button Pressed (Down)...\n");
					mass.push_back(100);
					break;
				//  Released
				case GLUT_UP:
					printf ("Mouse Left Button Released (Up)...\n");
					break;
			}

			break;

		//  Middle Button clicked
		case GLUT_MIDDLE_BUTTON:
			
			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					printf ("Mouse Middle Button Pressed (Down)...\n");
					break;
				//  Released
				case GLUT_UP:
					printf ("Mouse Middle Button Released (Up)...\n");
					break;
			}

			break;

		//  Right Button Clicked
		case GLUT_RIGHT_BUTTON:
			
			switch (state)
			{
				//  Pressed
				case GLUT_DOWN:
					printf ("Mouse Right Button Pressed (Down)...\n");
					break;
				//  Released
				case GLUT_UP:
					printf ("Mouse Right Button Released (Up)...\n");
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
	printf ("Mouse Drag Position: %d, %d.\n", x, y);
}

//-------------------------------------------------------------------------
//  This function is passed to the glutPassiveMotionFunc and is called 
//  whenever the mouse is moved.
//-------------------------------------------------------------------------
void pmotion (int x, int y)
{
	//  Print mouse move positopn
	printf ("Mouse Move Position: %d, %d.\n", x, y);
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



void main (int argc, sechar **argv)
{
	mass.reserve(8);

	btCollisionConfigurationPtr collisionConfiguration	= btCollisionConfigurationPtr( SENewObject<btDefaultCollisionConfiguration>() );
	btDispatcherPtr				dispatcher				= btDispatcherPtr ( SENewObject<btCollisionDispatcher>(collisionConfiguration.get()) );
	btBroadphaseInterfacePtr	overlappingPairCache	= btBroadphaseInterfacePtr( SENewObject<btDbvtBroadphase>() );
	btConstraintSolverPtr		solver					= btConstraintSolverPtr( SENewObject<btSequentialImpulseConstraintSolver>() );

	SEPhysicWorld::sharedInstance()->InitDiscreteDynamicsWorld( dispatcher ,overlappingPairCache, solver, collisionConfiguration );
	SEPhysicWorld::sharedInstance()->world()->setGravity(btVector3(0,-10,0));


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

	
	///create a few basic rigid bodies
	SEMeshPtr mesh = SEObjectStore::sharedInstance()->GetMesh( "Plane" );

	btTriangleMeshPtr triangleMesh = btTriangleMeshPtr( SENewObject<btTriangleMesh>() );
	mesh->GetTriangleMesh( triangleMesh );

	//btTriangleVertexArrayPtr vertexArray = mesh->CreateTriangleIndexVertexArray();

	btCollisionShape* boxShape = SENewObject<btBoxShape>(btVector3(btScalar(1.0),btScalar(1.0),btScalar(1.0)));
	btBvhTriangleMeshShape* triangleShape = SENewObject<btBvhTriangleMeshShape>( triangleMesh.get(), true, true );


	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0,0,0));

	{
		btScalar mass(0.0);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			triangleShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionState* myMotionState = SENewObject<btDefaultMotionState>(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,triangleShape,localInertia);

		physicObject1 = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
		physicObject1->Init( mesh, rbInfo );

		//add the body to the dynamics world
		SEPhysicWorld::sharedInstance()->AddObject( physicObject1 );
	}

	groundTransform.setOrigin(btVector3(0.0,5,0.5));

	{
		btScalar mass(0.1);

		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			boxShape->calculateLocalInertia(mass,localInertia);

		btDefaultMotionState* myMotionState = SENewObject<btDefaultMotionState>(groundTransform);
		btRigidBody::btRigidBodyConstructionInfo rbInfo(mass,myMotionState,boxShape,localInertia);

		physicObject2 = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
		physicObject2->Init( mesh, rbInfo );

		SEPhysicWorld::sharedInstance()->AddObject( physicObject2 );
	}


	//  Start GLUT event processing loop
	glutMainLoop();

	SEPhysicWorld::sharedInstance()->RemoveObjects();

}

