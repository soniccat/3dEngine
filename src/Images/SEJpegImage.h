
#ifndef SEJpegImage_H
#define SEJpegImage_H

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEImage.h"

class SEJpegImage: public SEImage
{
public:
	SEJpegImage(void);
	~SEJpegImage(void);

	void Load( const sechar* file );
};

#endif SEJpegImage_H