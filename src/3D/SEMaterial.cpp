#include "SEMaterial.h"
#include "SESceneLoader.h"
#include "SETools.h"

SEMaterial::SEMaterial( )
{
	
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

		case 2:
			if( streq( loader->dataType(), "name") )
			{
				SetName( loader->value1() ); 
			}
			break;

		default:
			SEAssert(false, "Unknow material value");
			break;
	}
}

void SEMaterial::Use()
{
	if( mTexture.get() )
		mTexture->Use();
}

void SEMaterial::SetName( const char* name )
{
	mName = name;
}

const SEString& SEMaterial::name()
{
	return mName;
}