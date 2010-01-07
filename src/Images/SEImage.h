
#ifndef SEImage_H
#define SEImage_H

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEIncludeOpenGL.h"


typedef shared_array<unsigned char> SEImageDataPtr;

//store original image data
class SEImage
{
protected:
	uint mWidth;
	uint mHeight;

	GLenum mPixelFormat;
	GLenum mPixelDataType;

	SEImageDataPtr mData;

public:
	SEImage(void);
	SEImage( uint width, uint height, SEImageDataPtr data );
	~SEImage(void);

	void Init( uint width, uint height, SEImageDataPtr data );
	void FreeData();
};

typedef shared_ptr<SEImage> SEImagePtr;

#endif SEImage_H