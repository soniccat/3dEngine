
#ifndef SEPhysicObject_H
#define SEPhysicObject_H

#include "SEIncludeLibrary.h"
#include "SEObjectInterface.h"
#include "SEMesh.h"


typedef shared_ptr<btRigidBody> btRigidBodyPtr;


class SEPhysicObject: public SEObjectInterface
{
	btRigidBodyPtr	mRigidBody;
	SEMeshPtr		mMesh;

public:
	SEPhysicObject();
	virtual ~SEPhysicObject(void);

	void Init( SEMeshPtr mesh, const btRigidBody::btRigidBodyConstructionInfo& info );

	virtual void Draw()=0;
};


#endif SEPhysicObject_H