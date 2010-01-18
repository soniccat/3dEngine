
#ifndef SETexture_H
#define SETexture_H

#include "SEIncludeOpenGL.h"
#include "SEIncludeLibrary.h"
#include "SEImage.h"
#include "SESceneLoaderDelegate.h"

class SETexture: public SESceneLoaderDelegate
{
	GLuint id;
	SEImagePtr mImage;

public:
	SETexture(void);
	~SETexture(void);

	void Init( const SEImagePtr image );
	void Use();
	void ParseData( SESceneLoader* loader );
};

typedef shared_ptr<SETexture> SETexturePtr;


#endif SETexture_H