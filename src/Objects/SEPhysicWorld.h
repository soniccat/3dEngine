
#ifndef SEPhysicWorld_H
#define SEPhysicWorld_H


#include "SEIncludeLibrary.h"
#include "SEPhysicObject.h"


class SEPhysicWorld;
typedef shared_ptr<SEPhysicWorld>			 SEPhysicWorldPtr;

typedef shared_ptr<btDynamicsWorld>			 btDynamicsWorldPtr;
typedef shared_ptr<btCollisionConfiguration> btCollisionConfigurationPtr;
typedef shared_ptr<btBroadphaseInterface>	 btBroadphaseInterfacePtr;
typedef shared_ptr<btDispatcher>			 btDispatcherPtr;
typedef shared_ptr<btConstraintSolver>		 btConstraintSolverPtr;


class SEPhysicWorld
{
	static SEPhysicWorldPtr		mInstance;

	btDynamicsWorldPtr			mWorld;
	SEPhysicObjectArray			mPhysicObjectArray;

	btCollisionConfigurationPtr	mCollisionConfiguration;
	btBroadphaseInterfacePtr	mBroadphaseInterface;
	btDispatcherPtr				mDispatcher;
	btConstraintSolverPtr		mConstraintSolver;

public:
	SEPhysicWorld(void);
	virtual ~SEPhysicWorld(void);

	static SEPhysicWorldPtr sharedInstance();
	void InitDiscreteDynamicsWorld( btDispatcherPtr dispatcher, btBroadphaseInterfacePtr broadphaseInterface, btConstraintSolverPtr constraintSolver, btCollisionConfigurationPtr collisionConfiguration );

	btDynamicsWorldPtr world();

	void Draw();

	void AddObject( SEPhysicObjectPtr object);
	void RemoveObjects();
};



#endif SEPhysicWorld_H