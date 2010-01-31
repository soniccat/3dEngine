
#ifndef SETouch_H
#define SETouch_H

#include "SEIncludeLibrary.h"

class SETouch;
typedef vector<SETouch> SETouchArray;

class SETouch
{
	float mX;
	float mY;

	//object to identificate touch: UITouch in iPhone
	void* mIdObj;

public:
	SETouch(void);
	SETouch(float x, float y);
	SETouch(float x, float y, void* obj);
	~SETouch(void);

	float x();
	float y();
	void* idObj();

	void SetX( float x );
	void SetY( float y );
};


#endif SETouch_H