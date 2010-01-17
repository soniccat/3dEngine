#include "SEPhysicObject.h"

SEPhysicObject::SEPhysicObject(void)
{
}

SEPhysicObject::~SEPhysicObject(void)
{
}

void SEPhysicObject::Init( SEMeshPtr mesh, const btRigidBody::btRigidBodyConstructionInfo& info )
{
	mRigidBody = btRigidBodyPtr( SENewObject<btRigidBody>( info ) );
}

void SEPhysicObject::Draw()
{
	btTransform trans;
	mRigidBody->getMotionState()->getWorldTransform(trans);

	glTranslatef( trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ() );
					
	btQuaternion quatern = trans.getRotation();
	btVector3 vec = quatern.getAxis();

	float radToGrad = 180.0/3.14;

	//printf("world pos = %f,%f,%f\n",float(trans.getOrigin().getX()),float(trans.getOrigin().getY()),float(trans.getOrigin().getZ()));
	//printf("world rot = %f,%f,%f,%f\n",quatern.getAngle(),vec.x(), vec.y(), vec.z());


	glRotatef( quatern.getAngle()*radToGrad, vec.x(), vec.y(), vec.z() );
	mMesh->Draw();
	glRotatef( -quatern.getAngle()*radToGrad, vec.x(), vec.y(), vec.z() );

	glTranslatef(-trans.getOrigin().getX(),-trans.getOrigin().getY(),-trans.getOrigin().getZ() );
}