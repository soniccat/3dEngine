#include "SEImage.h"

SEImage::SEImage(void)
{
	mWidth  = 0;
	mHeight = 0;

	mPixelFormat   = 0;
	mPixelDataType = 0;
}

SEImage::SEImage( uint width, uint height, SEImageDataPtr data )
{
	Init(width, height, data);
}

SEImage::~SEImage(void)
{
}

void SEImage::Init( uint width, uint height, SEImageDataPtr data )
{
	mPixelFormat   = 0;
	mPixelDataType = 0;

	mWidth  = width;
	mHeight = height;
	mData   = data;
}

void SEImage::FreeData()
{
	unsigned char* data = mData.get();
	mData = SEImageDataPtr();
	delete[] data;
}