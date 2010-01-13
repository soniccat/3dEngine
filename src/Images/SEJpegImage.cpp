#include "SEJpegImage.h"
#include "jpeglib.h"

SEJpegImage::SEJpegImage(void)
{
}

SEJpegImage::~SEJpegImage(void)
{
}

void SEJpegImage::Load( const sechar* filePath )
{	
	struct jpeg_decompress_struct cinfo;
	struct jpeg_error_mgr jerr;

	memset( &cinfo, 0 , sizeof(jpeg_decompress_struct) );
	memset( &jerr, 0 , sizeof(jpeg_error_mgr) );

	cinfo.err = jpeg_std_error( &jerr );
	jpeg_create_decompress( &cinfo );

	FILE* imageFile = fopen( filePath, "rb");
	SEAssert( imageFile, "image not open" );
	jpeg_stdio_src( &cinfo, imageFile );

	jpeg_read_header( &cinfo, 1 );
	jpeg_start_decompress( &cinfo );
	

	mWidth  = cinfo.image_width;
	mHeight = cinfo.image_height;
	mPixelDataType = GL_UNSIGNED_BYTE;

	switch( cinfo.output_components )
	{
	case 1:
		mPixelFormat = GL_LUMINANCE;
		break;
	case 3:
		mPixelFormat = GL_RGB; 
		break;
	default:
		SEAssert( false, "unsupported jpeg" );
	}

	int bits   = cinfo.output_components;	
	
	unsigned int size = mWidth * mHeight * bits;
	unsigned char* buffer =  ( unsigned char * ) malloc( size );
	unsigned char* row = buffer;

	while( cinfo.output_scanline < mHeight )
	{
		row = buffer   + 
			  bits  *
			  mWidth * 
			  cinfo.output_scanline;
		
		jpeg_read_scanlines( &cinfo, &row, 1 );
		
		printf("%d %d %d %d", row[0], row[1], row[2], row[3] );
	}

	mData = SEImageDataPtr( buffer );

	jpeg_finish_decompress ( &cinfo );
	jpeg_destroy_decompress( &cinfo ); 

	fclose( imageFile );
}