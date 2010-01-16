
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
	SEMaterial( );
	~SEMaterial(void);

	void SetName( const char* name );
	const SEString& name();
	
	void ParseData( SESceneLoader* loader );
	void SetTexture( SETexturePtr texture );

	void Use();
};

typedef shared_ptr<SEMaterial> SEMaterialPtr;
typedef vector< SEMaterialPtr, SEAllocator<SEMaterialPtr> > SEMaterialArray;


#endif SEMaterial_H