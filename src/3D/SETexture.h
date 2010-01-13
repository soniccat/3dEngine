
#ifndef SETexture_H
#define SETexture_H

#include "SEIncludeOpenGL.h"
#include "SEIncludeLibrary.h"

#include "SEImage.h"

class SETexture
{
	GLuint id;
	SEImagePtr mImage;

public:
	SETexture(void);
	~SETexture(void);

	void Init( const SEImagePtr image );
	void Use();
};

typedef shared_ptr<SETexture> SETexturePtr;


#endif SETexture_H