
#ifndef SEMaterial_H
#define SEMaterial_H

#include "SEIncludeLibrary.h"
#include "SESceneLoaderDelegate.h"
#include "SETexture.h"


class SEMaterial: public SESceneLoaderDelegate
{
	SEString mName;
	SETexturePtr mTexture;
	
public:
	SEMaterial( const char* name );
	~SEMaterial(void);
	
	void ParseData( SESceneLoader* loader );
	void SetTexture( SETexturePtr texture );

	void Use();
};

typedef shared_ptr<SEMaterial> SEMaterialPtr;


#endif SEMaterial_H