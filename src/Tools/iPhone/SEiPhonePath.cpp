#include "SEiPhonePath.h"
#include "SETools.h"
//#include "windows.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

void SEWindowsPath::CurrentDirectory(SEPathBase* outPath)
{	
	outPath->Init( [[[NSBundle mainBundle] bundlePath] cStringUsingEncoding:NSWindowsCP1251StringEncoding] );
}

void SEWindowsPath::Init( const sechar* _cString)
{
	SEAssert(exists(_cString), "exist path check" );
	
	SEPathBase::Init(_cString);

	//DWORD attributes = GetFileAttributes( _cString );
	//SEAssert(attributes != INVALID_FILE_ATTRIBUTES, "Getting file attribute check");

	mIsFolder = is_directory(_cString);
}

void SEWindowsPath::ChildArray(SEPathArray* pathArray) const
{
	SEAssert(mIsFolder, "is directory check" );
	SEAssert(mcString, "NULL check");

	sechar pathBuffer[EPATH_MAX_LENGHT+2];
	memset(pathBuffer,0,sizeof(pathBuffer));

	strcpy(pathBuffer, mcString);

	int len = strlen(pathBuffer);
	if( pathBuffer[ len-2 ] != '*' && pathBuffer[ len-1 ] != PATH_DELIMETER )
	{
		pathBuffer[ len ] = PATH_DELIMETER;
		pathBuffer[ len+1 ] = '*';
	}
	
	directory_iterator end_itr; // default construction yields past-the-end
	for ( directory_iterator itr( mcString ); itr != end_itr; ++itr )
	{
		SEPathPtr pathPtr( new SEPath );
		pathPtr->Init( itr->path().native_file_string().c_str() );
		pathArray->push_back( pathPtr );
	}

	/*WIN32_FIND_DATA findData;
	HANDLE searchHandle = FindFirstFile(pathBuffer, &findData);
	SEAssert( searchHandle != INVALID_HANDLE_VALUE, "Open directory check" );
	
	do
	{
		if( !streq( findData.cFileName, "." ) && !streq( findData.cFileName, ".." ) )
		{
			//build full path
			sechar currentPathBuffer[EPATH_MAX_LENGHT];
			memset(currentPathBuffer,0,sizeof(currentPathBuffer));
			strcpy(currentPathBuffer, mcString);
			if( currentPathBuffer[ len-1 ]!= PATH_DELIMETER )
				currentPathBuffer[ len ] = PATH_DELIMETER;

			strcpy( currentPathBuffer + strlen(currentPathBuffer), findData.cFileName );

			SEPathPtr pathPtr( new SEPath );
			pathPtr->Init( currentPathBuffer );
			pathArray->push_back( pathPtr );
		}
	}
	while(FindNextFile(searchHandle, &findData) != 0);

	FindClose(searchHandle);*/
}

bool SEWindowsPath::IsFolder() const
{
	return mIsFolder;
}