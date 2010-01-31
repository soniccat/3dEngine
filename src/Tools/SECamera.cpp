#include "SECamera.h"
#include "SEIncludeOpenGL.h"
#include "SESceneLoader.h"
#include "SETools.h"

SECamera::SECamera( const sechar* name )
{
	mName = name;
}

SECamera::SECamera( )
{
	mUpVector.setX(0);
	mUpVector.setY(1);
	mUpVector.setZ(0);
	mUpVector.setW(1);
}

SECamera::~SECamera(void)
{
}

void SECamera::Use()
{
	gluLookAt(	mPosition.x(),mPosition.y(),mPosition.z(),
				mSeePoint.x(),mSeePoint.y(),mSeePoint.z(),
				mUpVector.x(),mUpVector.y(),mUpVector.z());
}

void SECamera::ParseData( SESceneLoader* loader )
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
		if( streq( loader->dataType(), "name" ) )
		{
			SetName( loader->value1() );
		}

		break;

	case 4:
		if( streq( loader->dataType(), "pos" ) )
			SetPosition( btVector3( atof( loader->value1() ), atof( loader->value2() ), atof( loader->value3() ) ) );

		else if( streq( loader->dataType(), "see" ) )
			SetSeePoint( btVector3( atof( loader->value1() ), atof( loader->value2() ), atof( loader->value3() ) ) );

		break;
	}	
}

void SECamera::SetName( const char* name )
{
	mName = name;
}

const SEString& SECamera::name()
{
	return mName;
}

void SECamera::SetPosition( btVector3& position )
{
	mPosition = position;
}

void SECamera::SetSeePoint( btVector3& seePoint )
{
	mSeePoint = seePoint;
}

const btVector3& SECamera::postiton() const
{
	return mPosition;
}

const btVector3& SECamera::seePoint() const
{
	return mSeePoint;
}

const btVector3& SECamera::upVector() const
{
	return mUpVector;
}