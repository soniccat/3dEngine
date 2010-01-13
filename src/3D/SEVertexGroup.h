
#ifndef SEVertexGroup_H
#define SEVertexGroup_H


#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEAllocator.h"
#include "SESceneLoaderDelegate.h"
#include "SEMaterial.h"

class SEVertexGroup;

typedef shared_array<unsigned short> SEIndexArrayPtr;
typedef shared_ptr<SEVertexGroup> SEVertexGroupPtr;
typedef vector< SEVertexGroupPtr, SEAllocator<SEVertexGroupPtr> > SEVertexGroupArray;

class SEVertexGroup: public SESceneLoaderDelegate
{
	SEString mName;
	int mIndexArraySize;
	SEIndexArrayPtr mIndexArray;
	SEMaterialPtr mMaterial;

public:
	SEVertexGroup(void);
	~SEVertexGroup(void);

	void Init( SEIndexArrayPtr indexArray, int size );
	SEIndexArrayPtr indexArray();
	int indexArraySize();

	void SetFace( int index, float v1, float v2, float v3);
	void SetMaterial( SEMaterialPtr material );

	virtual void ParseData( SESceneLoader* loader );

	void SetName( const char* name );
	const SEString& name();
};


#endif SEVertexGroup_H