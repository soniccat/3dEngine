#include "SEImageLoader.h"
#include "SEIncludeLibrary.h"
#include "SEJpegImage.h"
#include "SETools.h"

SEImageLoader::SEImageLoader(void)
{
}

SEImageLoader::~SEImageLoader(void)
{
}

SEImagePtr SEImageLoader::Load( const sechar* filePath )
{
	return Load( SEPath( filePath ) );
}

SEImagePtr SEImageLoader::Load(const SEPath& filePath)
{
	SEString ext = filePath.Extension();
	SEImagePtr returnImagePtr;

	if( ext == ".jpg" )
	{
		SEJpegImage* jpegImage = new SEJpegImage;
		jpegImage->Load( filePath.cString() );

		returnImagePtr = SEImagePtr( jpegImage );

	}else
		SEAssert( false, "unknow image type" );

	return returnImagePtr;
}