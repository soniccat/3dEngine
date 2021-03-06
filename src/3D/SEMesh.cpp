#include "SEMesh.h"
#include "SETools.h"
#include "SESceneLoader.h"
#include "SEIncludeOpenGL.h"

#define MESHLOADER_BUFFER_SIZE 128


SEMesh::SEMesh(void)
{
	mVertexArraySize = -1;
}

SEMesh::~SEMesh(void)
{
	BREAKPOINTPLACE;
}

SEVertexNativeArrayPtr SEMesh::vertexArray()
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
	mVertexArray = SEVertexNativeArrayPtr( SENewArray<float>(count*3) );
	mNormalArray = SENormalNativeArrayPtr( SENewArray<float>(count*3) );
	mUVArray = SEUVNativeArrayPtr( SENewArray<float>(count*3) );
}

void SEMesh::SetVertex( int index, float x, float y, float z)
{
	SEAssert( index*3 < mVertexArraySize, "vertex bound check" );

	mVertexArray[index*3]   = x;
	mVertexArray[index*3+1] = y;
	mVertexArray[index*3+2] = z;
}

void SEMesh::SetNormal( int index, float x, float y, float z)
{
	SEAssert( index*3 < mVertexArraySize, "normal bound check" );

	mNormalArray[index*3]   = x;
	mNormalArray[index*3+1] = y;
	mNormalArray[index*3+2] = z;
}

void SEMesh::SetUV( int index, float u, float v )
{
	SEAssert( index*2 < mVertexArraySize, "uv bound check" );

	mUVArray[index*2]	= u;
	mUVArray[index*2+1] = v;
}

void SEMesh::AddVertexGroup( SEVertexGroupPtr group )
{
	mVertexGroupArray.push_back( group );
}

void SEMesh::ParseData( SESceneLoader* loader )
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
			SEVertexGroupPtr vertexGroup( SENewObject<SEVertexGroup>( loader->value1() ) );
			AddVertexGroup( vertexGroup );

			loader->AddDelegate( vertexGroup );
		}
		break;

	case 3:
		if( streq( loader->dataType(), "uv" ) )
		{
			SetUV( loader->currentIndex(), atof(loader->value1()), atof(loader->value2()) );
			loader->SetCurrentIndex( loader->currentIndex() + 1 );
		}
		break;

	case 4:
		if( streq( loader->dataType(), "vert" ) )
		{
			SetVertex( loader->currentIndex(), atof(loader->value1()), atof(loader->value2()), atof(loader->value3()) );
			loader->SetCurrentIndex( loader->currentIndex() + 1 );

		}else if( streq( loader->dataType(), "norm" ) )
		{
			SetNormal( loader->currentIndex(), atof(loader->value1()), atof(loader->value2()), atof(loader->value3()) );
			loader->SetCurrentIndex( loader->currentIndex() + 1 );
		
		}
		break;
	}

	if( !streq( loader->dataType(), "vert" ) && 
		!streq( loader->dataType(), "norm" ) &&
		!streq( loader->dataType(), "uv" ) )
		loader->SetCurrentIndex( 0 );
}

void SEMesh::Draw()
{
	SEVertexGroupArray::iterator start = mVertexGroupArray.begin();
	SEVertexGroupArray::iterator end   = mVertexGroupArray.end();
	
	SEIndexNativeArrayPtr  indexArrayPtr;

	/*for( int i=0; i<mVertexArraySize/3; ++i )
	{
		printf("%f %f \n", mUVArray[i*2], mUVArray[i*2+1]);
	}*/

	glVertexPointer( 3, GL_FLOAT, 0, mVertexArray.get() );
	glNormalPointer( GL_FLOAT, 0, mNormalArray.get() );

	if( mUVArray.get() )
		glTexCoordPointer( 2, GL_FLOAT, 0, mUVArray.get() );
	else
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	while( start != end )
	{
		(*start)->Draw();
		++start;
	}

	if( !mUVArray.get() )
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	SEGLAssert;
}

void SEMesh::GetTriangleMesh( btTriangleMeshPtr triangleMesh )
{
	SEVertexGroupArray::iterator start = mVertexGroupArray.begin();
	SEVertexGroupArray::iterator end   = mVertexGroupArray.end();

	int faceCount = 0;
	SEIndexNativeArrayPtr indexArray;

	while( start != end )
	{
		faceCount = (*start)->indexArraySize();
		indexArray = (*start)->indexArray();
		
		for( int i=0; i<faceCount; i+=3 )
		{
			triangleMesh->addTriangle( 				
					btVector3( mVertexArray[ indexArray[i]*3   ], mVertexArray[ indexArray[i]*3   +1 ], mVertexArray[ indexArray[i]*3   +2 ] ),
					btVector3( mVertexArray[ indexArray[i+1]*3 ], mVertexArray[ indexArray[i+1]*3 +1 ], mVertexArray[ indexArray[i+1]*3 +2 ] ),
					btVector3( mVertexArray[ indexArray[i+2]*3 ], mVertexArray[ indexArray[i+2]*3 +1 ], mVertexArray[ indexArray[i+2]*3 +2 ] )
				);
		}

		++start;
	}
}

btBoxShapePtr SEMesh::GetBoxShape( )
{
	float minX = FLT_MAX, maxX = FLT_MIN;
	float minY = FLT_MAX, maxY = FLT_MIN;
	float minZ = FLT_MAX, maxZ = FLT_MIN;

	float* vertexArray = mVertexArray.get();
	for( int i=0; i<mVertexArraySize; i+=3 )
	{
		if( minX > vertexArray[i] ) minX = vertexArray[i];
		if( maxX < vertexArray[i] ) maxX = vertexArray[i];

		if( minY > vertexArray[i+1] ) minY = vertexArray[i+1];
		if( maxY < vertexArray[i+1] ) maxY = vertexArray[i+1];

		if( minZ > vertexArray[i+2] ) minZ = vertexArray[i+2];
		if( maxZ < vertexArray[i+2] ) maxZ = vertexArray[i+2];
	}

	btVector3 vec =  btVector3( (maxX - minX)/2.0f,
								(maxY - minY)/2.0f,
								(maxZ - minZ)/2.0f );

	/*if( vec.x() < 0.1 ) 
		vec.setX(0.1f);
	if( vec.y() < 0.1 )
		vec.setY(0.1f);
	if( vec.z() < 0.1 ) 
		vec.setZ(0.1f);*/

	return btBoxShapePtr( SENewObject<btBoxShape>( vec ) );
}