#include "SELoader.h"
#include "SEMain.h"

SELoader::SELoader(void)
{
	mFileReader.SetHandler( this );
	mCurrentIndex = 0;
}

SELoader::~SELoader(void)
{
	mFileReader.Close();
}

void SELoader::Load(const SEPathBase* path)
{
	if( path->IsFolder() )
	{
		SEPathArray pathArray;
		path->ChildArray(&pathArray);

		for( uint i=0; i<pathArray.size(); ++i )
		{
			Load( pathArray[i].get() );
		}

	}else
	{
		mFileReader.Load( path );
	}
}

void SELoader::Close()
{
	mFileReader.Close();
}

void SELoader::AddDelegate( SELoaderDelegatePtr loaderDelegatePtr )
{
	mDelegateStack.push( loaderDelegatePtr );
}

void SELoader::PopDelegate( )
{
	mDelegateStack.pop();
}

void SELoader::HandleString(const sechar* string, bool isEndOfFile)
{
	mValidValueCount = sscanf(string,"%s %s %s %s", mDataType, mValue1, mValue2, mValue3);

	if( mValidValueCount == -1 || mValidValueCount == 0 )
		return;

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

int SELoader::validValueCount() const
{
	return mValidValueCount;
}

const sechar* SELoader::dataType() const
{
	return mDataType;
}

const sechar* SELoader::value1() const
{
	return mValue1;
}

const sechar* SELoader::value2() const
{
	return mValue2;
}

const sechar* SELoader::value3() const
{
	return mValue3;
}

void SELoader::SetCurrentIndex( int value )
{
	mCurrentIndex = value;
}

int SELoader::currentIndex()
{
	return mCurrentIndex;
}