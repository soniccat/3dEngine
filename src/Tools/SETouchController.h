
#ifndef SETouchController_H
#define SETouchController_H

#include "SEIncludeLibrary.h"
#include "SETouchControllerDelegate.h"
#include "SETouch.h"


class SETouchController;

typedef shared_ptr<SETouchController> SETouchControllerPtr;

enum SETouchingType
{
	SETouchingAddTouches,
	SETouchingMoveTouches,
	SETouchingEndTouches
};


//simply touch container
class SETouchController
{
	static SETouchControllerPtr mInstance;

	SETouchControllerDelegateArray mDelegateArray;
	int mPressedTouch;

	//touch buffer
	SETouchArray mModifyTouchArray;

public:
	SETouchController(void);
	~SETouchController(void);

	static SETouchControllerPtr sharedInstance();

	int pressedTouch();

	void AddHandler( SETouchControllerDelegatePtr obj );

	void BeginTouching();
	void AddTouch( SETouch touch );
	void EndTouching(SETouchingType type);
};


#endif SETouchController_H