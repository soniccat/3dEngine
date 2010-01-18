
#ifndef SEImageLoader_H
#define SEImageLoader_H

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEImage.h" 
#include "SEPathBase.h"

class SEImageLoader
{
public:
	SEImageLoader(void);
	~SEImageLoader(void);

	static void GetSupportedTypes( SEStringArray* outArray );
	static bool IsTypeSupported( const SEString& type );

	SEImagePtr Load(const SEPath& filePath);
	SEImagePtr Load(const sechar* filePath);
};

#endif SEImageLoader_H