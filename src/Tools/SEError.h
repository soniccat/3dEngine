
#ifndef SEError_H
#define SEError_H

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"

class SEError;

class SEErrorInterface
{
public:
	const SEError* error()const;
};

class SEError
{
	const char* mFileName;
	int mLine;

	SEString mDescription;

public:
	SEError(void);
	~SEError(void);

	void Init( const char* fileName, int line, const char* description );
	void Init( const char* fileName, int line, const SEString& description );
};

#define INIT_ERROR( s ) error.Init( __FILE__, __LINE__, s )

#endif SEError_H