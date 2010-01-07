
#ifndef SETexture_H
#define SETexture_H

#include "SEIncludeOpenGL.h"
#include "SEIncludeLibrary.h"

#include "SEImage.h"

class SETexture
{
	GLuint id;
	SEImagePtr image;

public:
	SETexture(void);
	~SETexture(void);

	void Init( const SEImagePtr image );
};


#endif SETexture_H