#include "SETexture.h"
#include "SESceneLoader.h"
#include "SETools.h"
#include "SEImageLoader.h"

SETexture::SETexture(void)
{
	id = -1;
}

SETexture::~SETexture(void)
{
	if( id != -1 )
		glDeleteTextures(1, &id);
}

void SETexture::Init( const SEImagePtr image )
{
	SEAssert( id == -1, "recreate now not support");

	mImage = image;

	glGenTextures( 1, &id );
	glBindTexture(GL_TEXTURE_2D, id );
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glTexImage2D( GL_TEXTURE_2D,
					  0,
					  image->pixelFormat(),
					  image->width(),
					  image->height(),
					  0,
					  image->pixelFormat(),
					  image->pixelDataType(),
					  image->data().get() ); 
}

void SETexture::Use()
{
	glBindTexture(GL_TEXTURE_2D, id );
}

void SETexture::ParseData( SESceneLoader* loader )
{
	switch( loader->validValueCount() )
	{
		case 1:
			if( streq( loader->dataType(), "end") )
			{
				loader->PopDelegate();
			}
			break;

		case 2:
			if( streq( loader->dataType(), "path") )
			{
				SEImageLoader imageLoader;

				SEPath path = loader->currentPath()->ParentPath();
				path.AppendName( loader->value1() );

				SEImagePtr image = imageLoader.Load( path.cString() );
				Init( image );
			}
			break;
	}
}