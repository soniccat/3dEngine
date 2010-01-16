#include "SESceneLoader.h"
#include "SEMain.h"

SESceneLoader::SESceneLoader(void)
{
	mFileReader.SetDelegate( this );
	mCurrentIndex = 0;
}

SESceneLoader::~SESceneLoader(void)
{
	mFileReader.Close();
}

void SESceneLoader::Load(const SEPathBase* path)
{
	TRACE(path->cString());
	
	if( path->IsFolder() )
	{
		//SEPath* debugPath;

		{
		SEPathArray pathArray;
		path->ChildArray(&pathArray);
		//debugPath = pathArray[0].get();

		for( uint i=0; i<pathArray.size(); ++i )
		{
			mCurrentPath = path;
			Load( pathArray[i].get() );
		}
		}

		//BREAKPOINTPLACE;
		//free( debugPath );

	}else
	{
		//if it is image then not load
		if( SEImageLoader::IsTypeSupported( path->Extension() ) )
			return;

		mCurrentPath = path;
		mFileReader.Load( path );
	}
}

void SESceneLoader::Close()
{
	mFileReader.Close();
}

void SESceneLoader::AddDelegate( SESceneLoaderDelegatePtr loaderDelegatePtr )
{
	mDelegateStack.push( loaderDelegatePtr );
}

void SESceneLoader::PopDelegate( )
{
	mDelegateStack.pop();
}

void SESceneLoader::HandleString(const sechar* string, bool isEndOfFile)
{
	memset( mDataType, 0, sizeof(mDataType) );
	mValidValueCount = sscanf(string,"%s %s %s %s", mDataType, mValue1, mValue2, mValue3);

	if( mDelegateStack.size() )
	{
		mDelegateStack.top()->ParseData( this );
		return;
	}

	if( mValidValueCount == 2 && streq( mDataType, "type" ) )
	{
		if( streq( mValue1, "Mesh" ) )
		{
			SEMeshPtr mesh( SENewObject<SEMesh>() );
			mDelegateStack.push( mesh );

			SEObjectStore::sharedInstance()->AddMesh( mesh );

		}else if( streq( mValue1, "Material" ) )
		{
			SEMaterialPtr material( SENewObject<SEMaterial>() );
			mDelegateStack.push( material );

			SEObjectStore::sharedInstance()->AddMaterial( material );
		}
	}
}

int SESceneLoader::validValueCount() const
{
	return mValidValueCount;
}

const sechar* SESceneLoader::dataType() const
{
	return mDataType;
}

const sechar* SESceneLoader::value1() const
{
	return mValue1;
}

const sechar* SESceneLoader::value2() const
{
	return mValue2;
}

const sechar* SESceneLoader::value3() const
{
	return mValue3;
}

void SESceneLoader::SetCurrentIndex( int value )
{
	mCurrentIndex = value;
}

int SESceneLoader::currentIndex()
{
	return mCurrentIndex;
}

const SEPathBase* SESceneLoader::currentPath()
{
	return mCurrentPath;
}