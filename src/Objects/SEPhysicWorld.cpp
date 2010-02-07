#include "SEPhysicWorld.h"

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"

SEPhysicWorldPtr SEPhysicWorld::mInstance;

SEPhysicWorld::SEPhysicWorld(void)
{
}

SEPhysicWorld::~SEPhysicWorld(void)
{
	RemoveObjects();
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

void SEPhysicWorld::Draw()
{
	SEPhysicObjectArray::iterator start = mPhysicObjectArray.begin();
	SEPhysicObjectArray::iterator end = mPhysicObjectArray.end();

	while(start != end)
	{
		(*start)->Draw();
		++start;
	}
}

void SEPhysicWorld::AddObject( SEPhysicObjectPtr object)
{
	mPhysicObjectArray.push_back( object );
	mWorld->addRigidBody( object->rigidBody().get() );
}

void SEPhysicWorld::RemoveObjects()
{
	for (int j= mWorld->getNumCollisionObjects()-1; j>=0 ;j--)
	{
		btRigidBody* obj = static_cast<btRigidBody*>( mWorld->getCollisionObjectArray()[j] );
		mWorld->removeRigidBody( obj );
	}

	mPhysicObjectArray.clear();
}