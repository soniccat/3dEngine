/*
 *		This Code Was Created By Jeff Molofee 2000
 *		A HUGE Thanks To Fredric Echols For Cleaning Up
 *		And Optimizing This Code, Making It More Flexible!
 *		If You've Found This Code Useful, Please Let Me Know.
 *		Visit My Site At nehe.gamedev.net
 */

#include "SEMain.h"
#include "SESceneLoader.h"
#include <vector>

#include "btBulletDynamicsCommon.h"

using namespace std;

#include "SEIncludeOpenGL.h"

//  Standard Input\Output C Library
#include <stdio.h>
#include <windowsx.h>


HDC			hDC=NULL;		// Private GDI Device Context
HGLRC		hRC=NULL;		// Permanent Rendering Context
HWND		hWnd=NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active=TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen=TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default

LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

int window_width = 800;
int window_height = 800;


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
		{
			leftButtonPressed = true;

			//for second sample
			SEPhysicObjectPtr washer = SEPhysicWorld::sharedInstance()->GetObject( "Washer" );

			btVector3 impulse( 0.1,0.1,1 );
			impulse.normalize();

			float powerValue = 18;
			btVector3 resultVector = powerValue*impulse;

			washer->rigidBody()->activate();

			washer->rigidBody()->getWorldTransform().setOrigin( btVector3(-2,5,-5) );
			washer->rigidBody()->setLinearVelocity( btVector3(0,0,0) );
			//washer->rigidBody()->setLinearVelocity( btVector3(0,0,0) );
			washer->rigidBody()->applyImpulse(resultVector, btVector3(0,0,0));
		}

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

			//printf( "dy\n", position.x(), position.y(), position.z() );

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


GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height==0)										// Prevent A Divide By Zero By
	{
		height=1;										// Making Height Equal One
	}

	/*
	glViewport(0,0,width,height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

	// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
	*/

		//  Stay updated with the window width and height
	window_width = width;
	window_height = height;

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
}

int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{
	/*glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	*/

	glClearColor (0.5, 0.5, 0.5, 1.0);
	SELoadDefaultOpenGLSettings();

	return TRUE;										// Initialization Went OK
}

int DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();									// Reset The Current Modelview Matrix

	SEGLAssert;


	SECameraPtr camera = SEObjectStore::sharedInstance()->GetCamera("Camera");
	camera->Use();

	SEGameLoop::sharedInstance()->Run();

	return TRUE;										// Everything Went OK
}

GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL,0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL,NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL,"Release Of DC And RC Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL,"Release Rendering Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		}
		hRC=NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd,hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL,"Release Device Context Failed.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hDC=NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL,"Could Not Release hWnd.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hWnd=NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL",hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL,"Could Not Unregister Class.","SHUTDOWN ERROR",MB_OK | MB_ICONINFORMATION);
		hInstance=NULL;									// Set hInstance To NULL
	}
}

/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
 *	title			- Title To Appear At The Top Of The Window				*
 *	width			- Width Of The GL Window Or Fullscreen Mode				*
 *	height			- Height Of The GL Window Or Fullscreen Mode			*
 *	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
 *	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/
 
BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left=(long)0;			// Set Left Value To 0
	WindowRect.right=(long)width;		// Set Right Value To Requested Width
	WindowRect.top=(long)0;				// Set Top Value To 0
	WindowRect.bottom=(long)height;		// Set Bottom Value To Requested Height

	fullscreen=fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance			= GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc		= (WNDPROC) WndProc;					// WndProc Handles Messages
	wc.cbClsExtra		= 0;									// No Extra Window Data
	wc.cbWndExtra		= 0;									// No Extra Window Data
	wc.hInstance		= hInstance;							// Set The Instance
	wc.hIcon			= LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground	= NULL;									// No Background Required For GL
	wc.lpszMenuName		= NULL;									// We Don't Want A Menu
	wc.lpszClassName	= "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,"Failed To Register The Window Class.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}
	
	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings,0,sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize=sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth	= width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight	= height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel	= bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL,"The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?","NeHe GL",MB_YESNO|MB_ICONEXCLAMATION)==IDYES)
			{
				fullscreen=FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL,"Program Will Now Close.","ERROR",MB_OK|MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle=WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle=WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle=WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle=WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

	// Create The Window
	if (!(hWnd=CreateWindowEx(	dwExStyle,							// Extended Style For The Window
								"OpenGL",							// Class Name
								title,								// Window Title
								dwStyle |							// Defined Window Style
								WS_CLIPSIBLINGS |					// Required Window Style
								WS_CLIPCHILDREN,					// Required Window Style
								0, 0,								// Window Position
								WindowRect.right-WindowRect.left,	// Calculate Window Width
								WindowRect.bottom-WindowRect.top,	// Calculate Window Height
								NULL,								// No Parent Window
								NULL,								// No Menu
								hInstance,							// Instance
								NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Window Creation Error.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};
	
	if (!(hDC=GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Device Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat=ChoosePixelFormat(hDC,&pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Find A Suitable PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!SetPixelFormat(hDC,PixelFormat,&pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Set The PixelFormat.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC=wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Create A GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if(!wglMakeCurrent(hDC,hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Can't Activate The GL Rendering Context.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd,SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL,"Initialization Failed.","ERROR",MB_OK|MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}


SETexturePtr objectTexture;
CameraControllerPtr cameraController;

//land with falling boxes - ground.blend
void LoadScene1()
{
	//physic world
	btCollisionConfigurationPtr collisionConfiguration	= btCollisionConfigurationPtr( SENewObject<btDefaultCollisionConfiguration>() );
	btDispatcherPtr				dispatcher				= btDispatcherPtr ( SENewObject<btCollisionDispatcher>(collisionConfiguration.get()) );
	btBroadphaseInterfacePtr	overlappingPairCache	= btBroadphaseInterfacePtr( SENewObject<btDbvtBroadphase>() );
	btConstraintSolverPtr		solver					= btConstraintSolverPtr( SENewObject<btSequentialImpulseConstraintSolver>() );

	SEPhysicWorld::sharedInstance()->InitDiscreteDynamicsWorld( dispatcher ,overlappingPairCache, solver, collisionConfiguration );
	SEPhysicWorld::sharedInstance()->world()->setGravity(btVector3(0,-9,0));


	SEPath currentPath;
	SEPath::CurrentDirectory( &currentPath );
	currentPath.AppendName( "sample1" );

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

	btCollisionShapePtr boxShape = cubeMesh->GetBoxShape(); //btCollisionShapePtr( SENewObject<btBoxShape>(btVector3(btScalar(1.0),btScalar(1.0),btScalar(1.0))) );
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

		SEPhysicObjectPtr physicObject = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
		physicObject->Init( mass, planeMesh, myMotionState, triangleMesh, triangleShape,localInertia );

		SEPhysicWorld::sharedInstance()->AddObject( physicObject );
	}

	groundTransform.setOrigin(btVector3(0.0,10,-30.0));
	groundTransform.setRotation( btQuaternion() );

	int z=1;
	int y=10;
	//for (int z=0;z<5;++z)
	//for (int y=10;y<15;++y)
	for (int i=0;i<5;++i)
	{
		groundTransform.setOrigin(btVector3(i*5.0,y*10,z*5.0));

		btScalar mass(0.1);

		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			boxShape->calculateLocalInertia(mass,localInertia);

		btDefaultMotionStatePtr myMotionState = btDefaultMotionStatePtr( SENewObject<btDefaultMotionState>(groundTransform) );

		SEPhysicObjectPtr physicObject = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
		physicObject->Init( mass, cubeMesh, myMotionState, boxShape, localInertia  );

		SEPhysicWorld::sharedInstance()->AddObject( physicObject );
	}
}

//continuous collision test - colisionTestt.blend
void LoadScene2()
{
	//physic world
	btCollisionConfigurationPtr collisionConfiguration	= btCollisionConfigurationPtr( SENewObject<btDefaultCollisionConfiguration>() );
	btDispatcherPtr				dispatcher				= btDispatcherPtr ( SENewObject<btCollisionDispatcher>(collisionConfiguration.get()) );
	btBroadphaseInterfacePtr	overlappingPairCache	= btBroadphaseInterfacePtr( SENewObject<btDbvtBroadphase>() );
	btConstraintSolverPtr		solver					= btConstraintSolverPtr( SENewObject<btSequentialImpulseConstraintSolver>() );

	//InitContinuousDynamicsWorld InitDiscreteDynamicsWorld
	SEPhysicWorld::sharedInstance()->InitDiscreteDynamicsWorld( dispatcher ,overlappingPairCache, solver, collisionConfiguration );
	SEPhysicWorld::sharedInstance()->world()->setGravity(btVector3(0,-9,0));
	SEPhysicWorld::sharedInstance()->world()->getDispatchInfo().m_enableSPU = true;

	SEPath currentPath;
	SEPath::CurrentDirectory( &currentPath );
	currentPath.AppendName( "sample2" );

	SESceneLoader loader;
	loader.Load( &currentPath );

	//camera
	cameraController = CameraControllerPtr( SENewObject<CameraController>() );
	SETouchController::sharedInstance()->AddDelegate( cameraController );
	
	///create a few basic rigid bodies
	SEMeshPtr planeMesh = SEObjectStore::sharedInstance()->GetMesh( "Plane" );
	SEMeshPtr washerMesh = SEObjectStore::sharedInstance()->GetMesh( "Washer" );
	SEMeshPtr wallMesh = SEObjectStore::sharedInstance()->GetMesh( "Wall" );

	//btTriangleMeshPtr triangleMesh = btTriangleMeshPtr( SENewObject<btTriangleMesh>() );
	//planeMesh->GetTriangleMesh( triangleMesh );

	//btTriangleVertexArrayPtr vertexArray = mesh->CreateTriangleIndexVertexArray();

	btCollisionShapePtr planeShape  = planeMesh->GetBoxShape();//btCollisionShapePtr( SENewObject<btBoxShape>(btVector3(btScalar(1.0),btScalar(1.0),btScalar(1.0))) );
	btCollisionShapePtr washerShape = washerMesh->GetBoxShape();
	btCollisionShapePtr wallShape = wallMesh->GetBoxShape();

	//planeShape->setMargin(gCollisionMargin);
	washerShape->setMargin(0.05f);
	//wallShape->setMargin(gCollisionMargin);

	//btBvhTriangleMeshShapePtr triangleShape = btBvhTriangleMeshShapePtr( SENewObject<btBvhTriangleMeshShape>( triangleMesh.get(), true, true ) );


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
			planeShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionStatePtr myMotionState = btDefaultMotionStatePtr( SENewObject<btDefaultMotionState>(groundTransform) );

		SEPhysicObjectPtr physicObject = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
		physicObject->Init( mass, planeMesh, myMotionState, planeShape,localInertia );

		SEPhysicWorld::sharedInstance()->AddObject( physicObject );
	}

	groundTransform.setOrigin(btVector3(0,0,10));

	{
		btScalar mass(0.0);

		//rigidbody is dynamic if and only if mass is non zero, otherwise static
		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			wallShape->calculateLocalInertia(mass,localInertia);

		//using motionstate is recommended, it provides interpolation capabilities, and only synchronizes 'active' objects
		btDefaultMotionStatePtr myMotionState = btDefaultMotionStatePtr( SENewObject<btDefaultMotionState>(groundTransform) );

		SEPhysicObjectPtr physicObject = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
		physicObject->Init( mass, wallMesh, myMotionState, wallShape,localInertia );

		SEPhysicWorld::sharedInstance()->AddObject( physicObject );
	}

	//groundTransform.setOrigin(btVector3(0.0,10,-30.0));
	groundTransform.setRotation( btQuaternion( btVector3(1,1,1),1 ) );
	//groundTransform.setIdentity();

	int z=-5;
	int y=5;
	int i=-2;
	{
		groundTransform.setOrigin(btVector3(i,y,z));

		btScalar mass(0.1);

		bool isDynamic = (mass != 0.f);

		btVector3 localInertia(0,0,0);
		if (isDynamic)
			washerShape->calculateLocalInertia(mass,localInertia);

		btDefaultMotionStatePtr myMotionState = btDefaultMotionStatePtr( SENewObject<btDefaultMotionState>(groundTransform) );

		SEPhysicObjectPtr physicObject = SEPhysicObjectPtr(SENewObject<SEPhysicObject>());
		physicObject->Init( mass, washerMesh, myMotionState, washerShape, localInertia  );

		// Only do CCD if  motion in one timestep (1.f/60.f) exceeds CUBE_HALF_EXTENTS
		physicObject->rigidBody()->setCcdMotionThreshold( 0.1 );

		//Experimental: better estimation of CCD Time of Impact:
		physicObject->rigidBody()->setCcdSweptSphereRadius( 0.2*0.2 );

		SEPhysicWorld::sharedInstance()->AddObject( physicObject );
	}
}

void LoadScene()
{
	LoadScene2();
}

LRESULT CALLBACK WndProc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_ACTIVATE:							// Watch For Window Activate Message
		{
			if (!HIWORD(wParam))					// Check Minimization State
			{
				active=TRUE;						// Program Is Active
			}
			else
			{
				active=FALSE;						// Program Is No Longer Active
			}

			return 0;								// Return To The Message Loop
		}

		case WM_SYSCOMMAND:							// Intercept System Commands
		{
			switch (wParam)							// Check System Calls
			{
				case SC_SCREENSAVE:					// Screensaver Trying To Start?
				case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
				return 0;							// Prevent From Happening
			}
			break;									// Exit
		}

		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}

		case WM_KEYDOWN:							// Is A Key Being Held Down?
		{
			keys[wParam] = TRUE;					// If So, Mark It As TRUE
			return 0;								// Jump Back
		}

		case WM_KEYUP:								// Has A Key Been Released?
		{
			keys[wParam] = FALSE;					// If So, Mark It As FALSE
			return 0;								// Jump Back
		}

		case WM_SIZE:								// Resize The OpenGL Window
		{
			ReSizeGLScene(LOWORD(lParam),HIWORD(lParam));  // LoWord=Width, HiWord=Height
			return 0;								// Jump Back
		}

		case WM_LBUTTONDOWN:
		case WM_RBUTTONDOWN:
		case WM_MBUTTONDOWN:
		case WM_LBUTTONUP:
		case WM_RBUTTONUP:
		case WM_MBUTTONUP:
		case WM_MOUSEMOVE:
		{
			int x =  GET_X_LPARAM(lParam); 
			int y =  GET_Y_LPARAM(lParam); 

			SETouchType touch = SETouchNone;
			SETouchButton button = SETouchButtonNone;
			
			if( uMsg == WM_LBUTTONDOWN || 
				uMsg == WM_RBUTTONDOWN ||
				uMsg == WM_MBUTTONDOWN )
					touch = SETouchBegin;
			
			else if( uMsg == WM_LBUTTONUP || 
					 uMsg == WM_RBUTTONUP ||
					 uMsg == WM_MBUTTONUP )
					touch = SETouchEnd;

			else if( uMsg == WM_MOUSEMOVE )
				touch = SETouchMove;


			if( uMsg == WM_LBUTTONUP || 
				uMsg == WM_LBUTTONDOWN)
					button = SETouchButtonLeft;

			else if( uMsg == WM_RBUTTONUP || 
					 uMsg == WM_RBUTTONDOWN)
					button = SETouchButtonRight;

			else if( uMsg == WM_MBUTTONUP || 
					 uMsg == WM_MBUTTONDOWN)
					 button = SETouchButtonMiddle;

			SETouchController::sharedInstance()->BeginTouching();
			SETouchController::sharedInstance()->AddTouch( SETouch( x,y ) );
			SETouchController::sharedInstance()->EndTouching( touch, button );
			return 0;
		}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{

	MSG		msg;									// Windows Message Structure
	BOOL	done=FALSE;								// Bool Variable To Exit Loop

	// Ask The User Which Screen Mode They Prefer
	//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen=FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Simple Engine example",640,480,16,fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}

	LoadScene();

	while(!done)									// Loop That Runs While done=FALSE
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))	// Is There A Message Waiting?
		{
			if (msg.message==WM_QUIT)				// Have We Received A Quit Message?
			{
				done=TRUE;							// If So done=TRUE
			}
			else									// If Not, Deal With Window Messages
			{
				TranslateMessage(&msg);				// Translate The Message
				DispatchMessage(&msg);				// Dispatch The Message
			}
		}
		else										// If There Are No Messages
		{
			// Draw The Scene.  Watch For ESC Key And Quit Messages From DrawGLScene()
			if (active)								// Program Active?
			{
				if (keys[VK_ESCAPE])				// Was ESC Pressed?
				{
					done=TRUE;						// ESC Signalled A Quit
				}
				else								// Not Time To Quit, Update Screen
				{
					DrawGLScene();					// Draw The Scene
					SwapBuffers(hDC);				// Swap Buffers (Double Buffering)
				}
			}

			if (keys[VK_F1])						// Is F1 Being Pressed?
			{
				keys[VK_F1]=FALSE;					// If So Make Key FALSE
				KillGLWindow();						// Kill Our Current Window
				fullscreen=!fullscreen;				// Toggle Fullscreen / Windowed Mode
				// Recreate Our OpenGL Window
				if (!CreateGLWindow("Simple Engine example",640,480,16,fullscreen))
				{
					return 0;						// Quit If Window Was Not Created
				}
			}
		}
	}

	// Shutdown
	KillGLWindow();									// Kill The Window
	return (msg.wParam);							// Exit The Program
}
