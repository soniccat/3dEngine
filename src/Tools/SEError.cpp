
#include "SEError.h"

SEError::SEError(void)
{
	mFileName = NULL;
	mLine = -1;
}

SEError::~SEError(void)
{
}

void SEError::Init( const char* fileName, int line, const char* description )
{
	Init( fileName, line, SEString( description ) );
}

void SEError::Init( const char* fileName, int line, const SEString& description )
{
	mFileName = fileName;
	mLine = line;

	//copy description
	mDescription = description;
}

