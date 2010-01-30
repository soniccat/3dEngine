
#ifndef SETouch_H
#define SETouch_H

#include "SEIncludeLibrary.h"

class SETouch;
typedef vector<SETouch> SETouchArray;

class SETouch
{
	float mX;
	float mY;

public:
	SETouch(void);
	~SETouch(void);

	float x();
	float y();
};


#endif SETouch_H