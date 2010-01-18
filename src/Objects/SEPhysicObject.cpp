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

void SEPhysicObject::Init( SEMeshPtr mesh, const btRigidBody::btRigidBodyConstructionInfo& info )
{
	mMesh = mesh;
	mRigidBody = btRigidBodyPtr( SENewObject<btRigidBody>( info ) );
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