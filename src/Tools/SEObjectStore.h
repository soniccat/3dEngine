

#include "SEMesh.h"

class SEObjectStore;

typedef shared_ptr<SEObjectStore> SEObjectStorePtr;

class SEObjectStore
{
	static SEObjectStorePtr mInstance;
	SEMeshArray mMeshArray;

public:
	SEObjectStore(void);
	~SEObjectStore(void);

	static SEObjectStorePtr sharedInstance();
	void AddMesh( SEMeshPtr mesh );
	SEMeshPtr GetMesh( const char* name );
};
