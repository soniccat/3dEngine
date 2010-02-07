
#ifndef SEPhysicObject_H
#define SEPhysicObject_H

#include "SEIncludeLibrary.h"
#include "SEObjectInterface.h"
#include "SEMesh.h"


typedef shared_ptr<btRigidBody> btRigidBodyPtr;

typedef shared_ptr<btMotionState> btMotionStatePtr;
typedef shared_ptr<btDefaultMotionState> btDefaultMotionStatePtr;

typedef shared_ptr<btCollisionShape> btCollisionShapePtr;
typedef shared_ptr<btBvhTriangleMeshShape> btBvhTriangleMeshShapePtr;
typedef shared_ptr<btCollisionShape> btCollisionShapePtr;

typedef shared_ptr<btStridingMeshInterface> btStridingMeshInterfacePtr;
typedef shared_ptr<btTriangleMeshShape> btTriangleMeshShapePtr;

class SEPhysicObject;
typedef shared_ptr<SEPhysicObject> SEPhysicObjectPtr;
typedef vector< SEPhysicObjectPtr > SEPhysicObjectArray;


class SEPhysicObject: public SEObjectInterface
{
	//bullet info
	btRigidBodyPtr		mRigidBody;
	btMotionStatePtr	mMotionState;
	btCollisionShapePtr mCollisionShape;
	btStridingMeshInterfacePtr mMeshInterface;

	SEMeshPtr		mMesh;

public:
	SEPhysicObject();
	virtual ~SEPhysicObject(void);

	void Init( btScalar mass, SEMeshPtr mesh, btMotionStatePtr motionState, btCollisionShapePtr shape, const btVector3& localInertia );
	void Init( btScalar mass, SEMeshPtr mesh, btMotionStatePtr motionState, btTriangleMeshPtr triangleMesh, btTriangleMeshShapePtr shape, const btVector3& localInertia );

	virtual void Draw();
	btRigidBodyPtr  rigidBody();
	SEMeshPtr		mesh();
};


#endif SEPhysicObject_H