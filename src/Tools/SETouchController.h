
#ifndef SETouchController_H
#define SETouchController_H

#include "SEIncludeLibrary.h"
#include "SETouchControllerDelegate.h"
#include "SETouch.h"


class SETouchController;

typedef shared_ptr<SETouchController> SETouchControllerPtr;

enum SETouchType
{
	SETouchNone,
	SETouchBegin,
	SETouchMove,
	SETouchEnd
};

enum SETouchButton
{
	SETouchButtonNone,
	SETouchButtonLeft,
	SETouchButtonMiddle,
	SETouchButtonRight
};


//simply touch container
class SETouchController
{
	static SETouchControllerPtr mInstance;

	SETouchControllerDelegateArray mDelegateArray;
	int mPressedTouchCount;

	//touch buffer
	SETouchArray mModifyTouchArray;

public:
	SETouchController(void);
	~SETouchController(void);

	static SETouchControllerPtr sharedInstance();

	int pressedTouchCount();

	void AddDelegate( SETouchControllerDelegatePtr obj );

	void BeginTouching();
	void AddTouch( SETouch touch );
	void EndTouching(SETouchType type, SETouchButton button);
	void EndTouching( SETouchType type );
};


#endif SETouchController_H