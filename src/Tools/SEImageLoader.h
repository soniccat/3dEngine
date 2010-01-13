
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

	SEImagePtr Load(const SEPath& filePath);
	SEImagePtr Load(const sechar* filePath);
};

#endif SEImageLoader_H