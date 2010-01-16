#include "SEMaterial.h"
#include "SESceneLoader.h"
#include "SETools.h"

SEMaterial::SEMaterial( const char* name )
{
	mName = name;
}

SEMaterial::~SEMaterial(void)
{
}

void SEMaterial::SetTexture( SETexturePtr texture )
{
	SEAssert( mTexture.get() == 0, "Texture already inited" );
	mTexture = texture;
}

void SEMaterial::ParseData( SESceneLoader* loader )
{
	switch( loader->validValueCount() )
	{
		case 1:
			if( streq( loader->dataType(), "end") )
			{
				loader->PopDelegate();
				
			}else if( streq( loader->dataType(), "texture") )
			{
				SETexturePtr texture = SETexturePtr( SENewObject<SETexture>() );
				SetTexture( texture );
				
				loader->AddDelegate( texture );
			}
			break;
	}
}

void SEMaterial::Use()
{
	if( mTexture.get() )
		mTexture->Use();
}