
#ifndef SEMesh_H
#define SEMesh_H


#include "SEIncludeLibrary.h"

#include "SEAllocator.h"
#include "SEVertexGroup.h"
#include "SEFileReaderBase.h"
#include "SESceneLoaderDelegate.h"

class SEMesh;
class SESceneLoader;

typedef shared_ptr<SEMesh> SEMeshPtr;
typedef vector< SEMeshPtr, SEAllocator<SEMeshPtr> > SEMeshArray;
typedef shared_array<float> SEVertexArrayPtr;
typedef shared_array<float> SENormalArrayPtr;
typedef shared_array<float> SEUVArrayPtr;

class SEMesh: public SESceneLoaderDelegate
{
	SEString mName;

	int mVertexArraySize;
	SEVertexArrayPtr mVertexArray;
	SENormalArrayPtr mNormalArray;
	SEUVArrayPtr	 mUVArray;
	
	SEVertexGroupArray mVertexGroupArray;

public:
	SEMesh(void);
	~SEMesh(void);

	SEVertexArrayPtr vertexArray();

	void SetName( const char* name );
	const SEString& name();

	void SetVertexArrayCount( int count );
	void SetVertex( int index, float x, float y, float z);
	void SetNormal( int index, float x, float y, float z);
	void SetUV( int index, float u, float v );

	void AddVertexGroup( SEVertexGroupPtr group );

	virtual void ParseData( SESceneLoader* loader );

	void Draw();
};

#endif SEMesh_H
