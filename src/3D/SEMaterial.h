
#ifndef SEMaterial_H
#define SEMaterial_H

#include "SEIncludeLibrary.h"
#include "SESceneLoaderDelegate.h"


class SEMaterial: public SESceneLoaderDelegate
{
public:
	SEMaterial(void);
	~SEMaterial(void);
};

typedef shared_ptr<SEMaterial> SEMaterialPtr;


#endif SEMaterial_H