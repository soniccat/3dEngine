#include "SEImageLoader.h"
#include "SEIncludeLibrary.h"
#include "SEJpegImage.h"

SEImageLoader::SEImageLoader(void)
{
}

SEImageLoader::~SEImageLoader(void)
{
}

SEImagePtr SEImageLoader::Load( const sechar* filePath )
{
	return Load( path( filePath ) );
}

SEImagePtr SEImageLoader::Load(const path& filePath)
{
	path fpath(filePath);
	path::string_type ext = fpath.extension();

	SEImagePtr returnImagePtr;

	if( ext == ".jpg" )
	{
		SEJpegImage* jpegImage = new SEJpegImage;
		jpegImage->Load( filePath.string().c_str() );

		returnImagePtr = SEImagePtr( jpegImage );

	}else
		SEAssert( false, "unknow image type" );

	return returnImagePtr;
}