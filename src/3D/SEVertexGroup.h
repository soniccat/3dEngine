
#ifndef SEVertexGroup_H
#define SEVertexGroup_H


#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEAllocator.h"
#include "SESceneLoaderDelegate.h"
#include "SEMaterial.h"

class SEVertexGroup;

typedef unsigned short SEIndexType;
typedef shared_array<SEIndexType> SEIndexNativeArrayPtr;
typedef shared_ptr<SEVertexGroup> SEVertexGroupPtr;
typedef vector< SEVertexGroupPtr, SEAllocator<SEVertexGroupPtr> > SEVertexGroupArray;

class SEVertexGroup: public SESceneLoaderDelegate
{
	SEString mName;
	int mIndexArraySize;
	SEIndexNativeArrayPtr mIndexArray;
	SEMaterialPtr mMaterial;

public:
	SEVertexGroup(const char* name);
	~SEVertexGroup(void);

	void Init( SEIndexNativeArrayPtr indexArray, int size );
	SEIndexNativeArrayPtr indexArray();
	int indexArraySize();

	void SetFace( int index, SEIndexType v1, SEIndexType v2, SEIndexType v3);
	void SetMaterial( SEMaterialPtr material );
	SEMaterialPtr material();
	

	virtual void ParseData( SESceneLoader* loader );
	void Draw();

	//void SetName( const char* name );
	const SEString& name();
};


#endif SEVertexGroup_H