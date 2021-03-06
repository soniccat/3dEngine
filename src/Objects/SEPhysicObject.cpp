#include "SEPhysicObject.h"
#include "SEDefinition.h"
#include "SEPhysicWorld.h"

SEPhysicObject::SEPhysicObject(void)
{
}

SEPhysicObject::~SEPhysicObject(void)
{
	//SEPhysicWorld::sharedInstance()->world()->removeRigidBody( mRigidBody.get() );
}

void SEPhysicObject::Init( btScalar mass, SEMeshPtr mesh, btMotionStatePtr motionState, btTriangleMeshPtr triangleMesh, btTriangleMeshShapePtr shape, const btVector3& localInertia )
{
	mMesh			= mesh;
	mMotionState	= motionState;
	mCollisionShape = shape;
	mMeshInterface  = triangleMesh;

	btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, motionState.get(), shape.get(), localInertia );
	mRigidBody = btRigidBodyPtr( SENewObject<btRigidBody>( rbInfo ) );
}

void SEPhysicObject::Init( btScalar mass, SEMeshPtr mesh, btMotionStatePtr motionState, btCollisionShapePtr shape, const btVector3& localInertia )
{
	mMesh			= mesh;
	mMotionState	= motionState;
	mCollisionShape = shape;

	btRigidBody::btRigidBodyConstructionInfo rbInfo( mass, motionState.get(), shape.get(), localInertia );
	mRigidBody = btRigidBodyPtr( SENewObject<btRigidBody>( rbInfo ) );
}


void SEPhysicObject::Draw()
{
	btTransform trans;
	mRigidBody->getMotionState()->getWorldTransform(trans);

	glTranslatef( trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() );

	//FIXME: replace rotation for increase perfomance
	btQuaternion quatern = trans.getRotation();
	btVector3 vec = quatern.getAxis();

	glRotatef( quatern.getAngle()*RAD_TO_DEG, vec.x(), vec.y(), vec.z() );
	mMesh->Draw();
	glRotatef( -quatern.getAngle()*RAD_TO_DEG, vec.x(), vec.y(), vec.z() );

	glTranslatef(-trans.getOrigin().getX(),-trans.getOrigin().getY(),-trans.getOrigin().getZ() );
}

btRigidBodyPtr SEPhysicObject::rigidBody()
{
	return mRigidBody;
}

const SEString& SEPhysicObject::name()
{
	return mMesh->name();
}