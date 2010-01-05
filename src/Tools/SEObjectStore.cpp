#include "SEObjectStore.h"
#include "SETools.h"

SEObjectStorePtr SEObjectStore::mInstance;

SEObjectStore::SEObjectStore(void)
{
}

SEObjectStore::~SEObjectStore(void)
{
	BREAKPOINTPLACE;
}

SEObjectStorePtr SEObjectStore::sharedInstance()
{
	if( mInstance.get() == 0 )
	{
		mInstance = SEObjectStorePtr( new SEObjectStore );
	}

	return mInstance;
}

void SEObjectStore::AddMesh( SEMeshPtr mesh )
{
	mMeshArray.push_back( mesh );
}

SEMeshPtr SEObjectStore::GetMesh( const char* name )
{
	SEMeshArray::iterator start = mMeshArray.begin();
	SEMeshArray::iterator end = mMeshArray.end();

	while( start != end )
	{
		if( streq( (*start)->name().c_str(), name) )
			return *start;

		++start;
	}

	SEAssert(false, "Mesh not found");
	return SEMeshPtr();
}