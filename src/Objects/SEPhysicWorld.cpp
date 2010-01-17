#include "SEPhysicWorld.h"

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"

SEPhysicWorldPtr SEPhysicWorld::mInstance;

SEPhysicWorld::SEPhysicWorld(void)
{
}

SEPhysicWorld::~SEPhysicWorld(void)
{
	BREAKPOINTPLACE;
}

SEPhysicWorldPtr SEPhysicWorld::sharedInstance()
{
	if( mInstance.get() == 0 )
	{
		mInstance = SEPhysicWorldPtr( SENewObject<SEPhysicWorld>() );
	}

	return mInstance;
}

void SEPhysicWorld::InitDiscreteDynamicsWorld( btDispatcherPtr dispatcher, btBroadphaseInterfacePtr broadphaseInterface, btConstraintSolverPtr constraintSolver, btCollisionConfigurationPtr collisionConfiguration )
{
	mCollisionConfiguration = collisionConfiguration;
	mBroadphaseInterface	= broadphaseInterface;
	mDispatcher				= dispatcher;
	mConstraintSolver		= constraintSolver;

	mWorld = btDynamicsWorldPtr( SENewObject<btDiscreteDynamicsWorld>( mDispatcher.get(), mBroadphaseInterface.get(), mConstraintSolver.get(), mCollisionConfiguration.get() ) );
}

btDynamicsWorldPtr SEPhysicWorld::world()
{
	return mWorld;
}