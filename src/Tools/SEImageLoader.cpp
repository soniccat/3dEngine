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

void SEImageLoader::GetSupportedTypes( SEStringArray* outArray )
{
	SEAssert( outArray->size() == 0, "Out array not empty" );
	outArray->push_back( SEString(".jpg") );
}

bool SEImageLoader::IsTypeSupported( const SEString& type )
{
	SEStringArray supportedFormats;
	SEImageLoader::GetSupportedTypes( &supportedFormats );

	for( uint i=0; i<supportedFormats.size();++i )
		if( supportedFormats[i] == type )
			return true;

	return false;
}

SEImagePtr SEImageLoader::Load( const sechar* filePath )
{
	return Load( SEPath( filePath ) );
}

SEImagePtr SEImageLoader::Load(const SEPath& filePath)
{
	TRACE2( "Load file %s", filePath.cString() );
	
	SEString ext = filePath.Extension();
	SEImagePtr returnImagePtr;

	if( ext == ".jpg" )
	{
		SEJpegImage* jpegImage = SENewObject<SEJpegImage>();
		jpegImage->Load( filePath.cString() );

		returnImagePtr = SEImagePtr( jpegImage );

	}else
		SEAssert( false, "unknow image type" );

	return returnImagePtr;
}