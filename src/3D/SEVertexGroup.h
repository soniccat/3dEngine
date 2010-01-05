#pragma once

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEAllocator.h"
#include "SELoaderDelegate.h"

class SEVertexGroup;

typedef shared_array<unsigned short> SEIndexArrayPtr;
typedef shared_ptr<SEVertexGroup> SEVertexGroupPtr;
typedef vector< SEVertexGroupPtr, SEAllocator<SEVertexGroupPtr> > SEVertexGroupArray;


class SEVertexGroup: public SELoaderDelegate
{
	SEString mName;
	int mIndexArraySize;
	SEIndexArrayPtr mIndexArray;

public:
	SEVertexGroup(void);
	~SEVertexGroup(void);

	void Init( SEIndexArrayPtr indexArray, int size );
	SEIndexArrayPtr indexArray();
	int indexArraySize();

	void SetFace( int index, float v1, float v2, float v3);

	virtual void ParseData( SELoader* loader );

	void SetName( const char* name );
	const SEString& name();
};
