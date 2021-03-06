
#include "SEMemory.h"
#include "SEPathBase.h"


#if (TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE)
#include <Foundation/Foundation.h>
#endif

void SEPathBase::CurrentDirectory(SEPathBase* outPath)
{
#if (TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE)
	
	outPath->Init( [[[NSBundle mainBundle] bundlePath] cStringUsingEncoding:NSWindowsCP1251StringEncoding] );
	TRACE( outPath->cString() );
	
#else
	path pt = current_path<path>( );
	TRACE( pt.string().c_str() );
	
	outPath->Init( pt.string().c_str() );
#endif
}

SEPathBase::SEPathBase(const sechar* _cString)
{
	Init( _cString );
}

SEPathBase::SEPathBase(void)
{
	BREAKPOINTPLACE;
}

SEPathBase::SEPathBase(const SEPathBase* pathBase)
{
	Init( pathBase->cString() );
}

SEPathBase::~SEPathBase(void)
{
	BREAKPOINTPLACE;
}

void SEPathBase::Init( const sechar* _cString)
{
	SEAssert( strlen(_cString) < EPATH_MAX_LENGHT, "path length check" );
	mPath/=_cString;
}

const sechar* SEPathBase::cString() const
{
	return mPath.string().c_str();
}

const sechar* SEPathBase::name() const
{
	/*SEAssert( mcString, "path must exist" );

	int delimeterIndex = -1;
	int len = strlen( mcString );
	for( int i=len; --i>=0; )
		if( mcString[i] == PATH_DELIMETER )
		{
			delimeterIndex = i;
			break;
		}

	return mcString + delimeterIndex;*/

	return mPath.filename().c_str();
}

void SEPathBase::AppendName( const char* name )
{
	//append
	mPath /= name;
}

void SEPathBase::ChildArray(SEPathArray* pathArray)  const
{
	SEAssert( IsFolder(), "is directory check" );
	SEAssert( mPath.string().length(), "NULL check");
	
	directory_iterator end_itr;
	for ( directory_iterator itr( mPath ); itr != end_itr; ++itr )
	{
		SEPathPtr pathPtr( SENewObject<SEPath>() );
		pathPtr->Init( itr->path().string().c_str() );
		pathArray->push_back( pathPtr );
	}
}

bool SEPathBase::IsFolder() const
{
	return is_directory( mPath );
}

SEPathBase SEPathBase::ParentPath() const
{
	return SEPathBase( mPath.parent_path().string().c_str() );
}

const SEString SEPathBase::Extension() const
{
	return SEString( mPath.extension().c_str() );
}