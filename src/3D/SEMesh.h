
#ifndef SEMesh_H
#define SEMesh_H


#include "SEIncludeLibrary.h"

#include "SEAllocator.h"
#include "SEVertexGroup.h"
#include "SEFileReaderBase.h"
#include "SELoaderDelegate.h"

class SEMesh;
class SELoader;

typedef shared_ptr<SEMesh> SEMeshPtr;
typedef vector< SEMeshPtr, SEAllocator<SEMeshPtr> > SEMeshArray;
typedef shared_array<float> SEVertexArrayPtr;


class SEMesh: public SELoaderDelegate
{
	SEString mName;

	int mVertexArraySize;
	SEVertexArrayPtr mVertexArray;
	
	SEVertexGroupArray mVertexGroupArray;

public:
	SEMesh(void);
	~SEMesh(void);

	SEVertexArrayPtr vertexArray();

	void SetName( const char* name );
	const SEString& name();

	void SetVertexArrayCount( int count );
	void SetVertex( int index, float x, float y, float z);

	void AddVertexGroup( SEVertexGroupPtr group );

	virtual void ParseData( SELoader* loader );

	void Draw();
};

#endif SEMesh_H
