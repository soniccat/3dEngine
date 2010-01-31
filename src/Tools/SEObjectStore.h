

#include "SEMesh.h"
#include "SECamera.h"

class SEObjectStore;

typedef shared_ptr<SEObjectStore> SEObjectStorePtr;

class SEObjectStore
{
	static SEObjectStorePtr mInstance;
	SEMeshArray mMeshArray;
	SEMaterialArray mMaterialArray;
	SECameraArray mCameraArray;

public:
	SEObjectStore(void);
	~SEObjectStore(void);

	static SEObjectStorePtr sharedInstance();

	void AddMesh( SEMeshPtr mesh );
	SEMeshPtr GetMesh( const char* name );

	void AddMaterial( SEMaterialPtr material );
	SEMaterialPtr GetMaterial( const char* name );

	void AddCamera( SECameraPtr camera );
	SECameraPtr GetCamera( const char* name );
};
