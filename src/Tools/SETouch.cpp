#include "SETouch.h"

SETouch::SETouch(void)
{
	SetX(0);
	SetY(0);
	mIdObj = NULL;
}

SETouch::SETouch( float x, float y )
{
	SetX(x);
	SetY(y);
	mIdObj = NULL;
}

SETouch::SETouch(float x, float y, void* obj)
{
	SetX(x);
	SetY(y);
	mIdObj = obj;
}

SETouch::~SETouch(void)
{
}

void SETouch::SetX( float x )
{
	mX = x;
}

void SETouch::SetY( float y )
{
	mY = y;
}

void* SETouch::idObj()
{
	return mIdObj;
}

float SETouch::x()
{
	return mX;
}

float SETouch::y()
{
	return mY;
}

