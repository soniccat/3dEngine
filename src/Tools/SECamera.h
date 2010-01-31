
#ifndef SECamera_H
#define SECamera_H

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SESceneLoaderDelegate.h"

class SECamera;

typedef shared_ptr<SECamera> SECameraPtr;
typedef vector<SECameraPtr>  SECameraArray;

//simple wrapper for gluLookAt
class SECamera: public SESceneLoaderDelegate
{
	//for find in SEObjectStore
	SEString  mName;

	btVector3 mPosition;
	btVector3 mSeePoint;
	btVector3 mUpVector;
	
public:
	SECamera( const sechar* name );
	SECamera( );
	~SECamera(void);
	
	void Use();

	void ParseData( SESceneLoader* loader );

	void SetName( const char* name );
	const SEString& name();


	void SetPosition( btVector3& position );
	void SetSeePoint( btVector3& seePoint );
	void SetUpVector( btVector3& upVector );

	const btVector3& postiton() const;
	const btVector3& seePoint() const;
	const btVector3& upVector() const;
};


#endif SECamera_H