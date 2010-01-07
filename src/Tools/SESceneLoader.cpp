#include "SESceneLoader.h"
#include "SEMain.h"

SESceneLoader::SESceneLoader(void)
{
	mFileReader.SetHandler( this );
	mCurrentIndex = 0;
}

SESceneLoader::~SESceneLoader(void)
{
	mFileReader.Close();
}

void SESceneLoader::Load(const SEPathBase* path)
{
	if( path->IsFolder() )
	{
		//SEPath* debugPath;

		{
		SEPathArray pathArray;
		path->ChildArray(&pathArray);
		//debugPath = pathArray[0].get();

		for( uint i=0; i<pathArray.size(); ++i )
		{
			Load( pathArray[i].get() );
		}
		}

		//BREAKPOINTPLACE;
		//free( debugPath );

	}else
	{
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
			SEMeshPtr mesh( new SEMesh );
			mDelegateStack.push( mesh );

			SEObjectStore::sharedInstance()->AddMesh( mesh );
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