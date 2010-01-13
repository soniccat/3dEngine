#include "SEVertexGroup.h"
#include "SESceneLoader.h"
#include "SETools.h"

SEVertexGroup::SEVertexGroup(void)
{
	mIndexArraySize = -1;
}

SEVertexGroup::~SEVertexGroup(void)
{
	BREAKPOINTPLACE;
}

void SEVertexGroup::Init( SEIndexArrayPtr indexArray, int size )
{
	SEAssert( mIndexArraySize == -1, "Object already inited" );

	mIndexArray = indexArray;
	mIndexArraySize = size;
}

SEIndexArrayPtr SEVertexGroup::indexArray()
{
	return mIndexArray;
}

int SEVertexGroup::indexArraySize()
{
	return mIndexArraySize;
}

void SEVertexGroup::SetFace( int index, float v1, float v2, float v3)
{
	SEAssert( index*3 < mIndexArraySize, "vertex index bound check" );

	mIndexArray[index*3    ] = v1;
	mIndexArray[index*3 + 1] = v2;
	mIndexArray[index*3 + 2] = v3;
}

void SEVertexGroup::ParseData( SESceneLoader* loader )
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
		if( streq( loader->dataType(), "vertexIndexCount" ) )
		{
			int size = atoi( loader->value1() );
			SEAssert( size > 0, "vertexIndexCount value check" );

			SEIndexArrayPtr arrayPtr( new unsigned short[ size*3 ] );
			Init( arrayPtr, size*3 );
		
		}/*else if()
		{
			SEMaterialPtr material( new SEMaterial );
			SetMaterial();
		}*/
		break;

	case 4:
		if( streq( loader->dataType(), "face" ) )
		{
			/*printf("%d %d %d\n", atoi( loader->value1() ), atoi( loader->value2() ), atoi( loader->value3()) );

			if( atoi( loader->value1()) == 25 && 
				atoi( loader->value2()) == 96 && 
				atoi( loader->value3()) == 73 )
			{
				BREAKPOINTPLACE;
			}*/

			SetFace( loader->currentIndex(), atoi( loader->value1() ), atoi( loader->value2() ), atoi( loader->value3() ) );
			loader->SetCurrentIndex( loader->currentIndex() + 1 );
		}
		break;
	}

	if( !streq( loader->dataType(), "face" ) )
		loader->SetCurrentIndex( 0 );
}

void SEVertexGroup::SetName( const char* name )
{
	mName = SEString(name);
}

const SEString& SEVertexGroup::name()
{
	return mName;
}