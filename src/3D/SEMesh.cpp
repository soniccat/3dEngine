#include "SEMesh.h"
#include "SETools.h"
#include "SELoader.h"

#if (TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE)
#import <OpenGLES/ES1/gl.h>
#import <OpenGLES/ES1/glext.h>
#else
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#define MESHLOADER_BUFFER_SIZE 128


SEMesh::SEMesh(void)
{
	mVertexArraySize = -1;
}

SEMesh::~SEMesh(void)
{
	BREAKPOINTPLACE;
}

SEVertexArrayPtr SEMesh::vertexArray()
{
	return mVertexArray;
}

void SEMesh::SetName( const char* name )
{
	mName = SEString(name);
}

const SEString& SEMesh::name()
{
	return mName;
}

void SEMesh::SetVertexArrayCount( int count )
{
	SEAssert( mVertexArray.get() == 0, "not allocated check" );
	mVertexArraySize = count*3;
	mVertexArray = SEVertexArrayPtr( new float[count*3] );
}

void SEMesh::SetVertex( int index, float x, float y, float z)
{
	SEAssert( index*3 < mVertexArraySize, "vertex bound check" );

	mVertexArray[index*3]   = x;
	mVertexArray[index*3+1] = y;
	mVertexArray[index*3+2] = z;
}

void SEMesh::AddVertexGroup( SEVertexGroupPtr group )
{
	mVertexGroupArray.push_back( group );
}

void SEMesh::ParseData( SELoader* loader )
{
	switch( loader->validValueCount() )
	{
	case 1:
		if( streq( loader->dataType(), "end") )
		{
			loader->PopDelegate();
		}
		break;

	case 2:
		if( streq( loader->dataType(), "vertexCount" ) )
		{
			int size = atoi( loader->value1() );
			SEAssert( size > 0, "vertextCount check" );

			SetVertexArrayCount( size );
		
		}else if( streq( loader->dataType(), "name" ) )
		{
			SetName( loader->value1() );

		}else if( streq( loader->dataType(), "vertexGroup" ) )
		{
			SEVertexGroupPtr vertexGroup( new SEVertexGroup );
			vertexGroup->SetName( loader->value1() );
			AddVertexGroup( vertexGroup );

			loader->AddDelegate( vertexGroup );
		}
		break;

	case 4:
		if( streq( loader->dataType(), "vert" ) )
		{
			SetVertex( loader->currentIndex(), atof(loader->value1()), atof(loader->value2()), atof(loader->value3()) );
			loader->SetCurrentIndex( loader->currentIndex() + 1 );
		}
		break;
	}

	if( !streq( loader->dataType(), "vert" ) )
		loader->SetCurrentIndex( 0 );
}

void SEMesh::Draw()
{
	SEVertexGroupArray::iterator start = mVertexGroupArray.begin();
	SEVertexGroupArray::iterator end   = mVertexGroupArray.end();
	
	SEIndexArrayPtr  indexArrayPtr;

	glEnableClientState( GL_VERTEX_ARRAY );

	while( start != end )
	{
		indexArrayPtr = (*start)->indexArray();

		glVertexPointer( 3, GL_FLOAT, 0, mVertexArray.get() );
		glDrawElements( GL_TRIANGLES, (*start)->indexArraySize() ,GL_UNSIGNED_SHORT, indexArrayPtr.get() );

		++start;
	}
}