#include "SEWindowsPath.h"
#include "SETools.h"
#include "windows.h"

#include <boost/filesystem.hpp>
using namespace boost::filesystem;

void SEWindowsPath::Init( const sechar* _cString)
{
}

void SEWindowsPath::ChildArray(SEPathArray* pathArray) const
{
	SEAssert(mPath.,"NULL check");

	sechar pathBuffer[EPATH_MAX_LENGHT+2];
	memset(pathBuffer,0,sizeof(pathBuffer));

	strcpy(pathBuffer, mcString);

	int len = strlen(pathBuffer);
	if( pathBuffer[ len-2 ] != '*' && pathBuffer[ len-1 ] != PATH_DELIMETER )
	{
		pathBuffer[ len ] = PATH_DELIMETER;
		pathBuffer[ len+1 ] = '*';
	}

	WIN32_FIND_DATA findData;
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

			SEPathPtr pathPtr( new EPath );
			pathPtr->Init( currentPathBuffer );
			pathArray->push_back( pathPtr );
		}
	}
	while(FindNextFile(searchHandle, &findData) != 0);

	FindClose(searchHandle);
}

bool SEWindowsPath::IsFolder() const
{
	return mIsFolder;
}