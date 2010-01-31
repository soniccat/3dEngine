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
		mInstance = SEObjectStorePtr( SENewObject<SEObjectStore>() );
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

void SEObjectStore::AddMaterial( SEMaterialPtr material )
{
	mMaterialArray.push_back( material );
}

SEMaterialPtr SEObjectStore::GetMaterial( const char* name )
{
	SEMaterialArray::iterator start = mMaterialArray.begin();
	SEMaterialArray::iterator end = mMaterialArray.end();

	while( start != end )
	{
		if( streq( (*start)->name().c_str(), name) )
			return *start;

		++start;
	}

	SEAssert(false, "Material not found");
	return SEMaterialPtr();
}

void SEObjectStore::AddCamera( SECameraPtr camera )
{
	mCameraArray.push_back( camera );
}

SECameraPtr SEObjectStore::GetCamera( const char* name )
{
	SECameraArray::iterator start = mCameraArray.begin();
	SECameraArray::iterator end = mCameraArray.end();

	while( start != end )
	{
		if( streq( (*start)->name().c_str(), name) )
			return *start;

		++start;
	}

	SEAssert(false, "Camera not found");
	return SECameraPtr();
}
