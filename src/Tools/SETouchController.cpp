
#include "SETouchController.h"
#include "SEDefinition.h"


SETouchControllerPtr SETouchController::mInstance;

SETouchController::SETouchController(void)
{
	mPressedTouchCount = 0;
}

SETouchController::~SETouchController(void)
{
}

SETouchControllerPtr SETouchController::sharedInstance()
{
	if( mInstance.get() == NULL )
		mInstance = SETouchControllerPtr( SENewObject<SETouchController>() );

	return mInstance;
}

void SETouchController::AddHandler( SETouchControllerDelegatePtr obj )
{
	mDelegateArray.push_back( obj );
}

void SETouchController::BeginTouching()
{
	SEAssert( !mModifyTouchArray.size(), "Begin touch when it began" );
}

void SETouchController::AddTouch( SETouch touch )
{
	mModifyTouchArray.push_back( touch );
}

void SETouchController::EndTouching( SETouchType type, SETouchButton button )
{
	SEAssert( mModifyTouchArray.size(), "End not begin touch" );
	
	SETouchControllerDelegateArray::iterator start = mDelegateArray.begin();
	SETouchControllerDelegateArray::iterator end = mDelegateArray.end();

	while( start != end )
	{
		switch( type )
		{
			case SETouchBegin:
				mPressedTouchCount += mModifyTouchArray.size();
				(*start)->TouchesBegin( mModifyTouchArray.begin(), mModifyTouchArray.size(), button );
				break;

			case SETouchMove:
				(*start)->TouchesMove( mModifyTouchArray.begin(), mModifyTouchArray.size(), button );
				break;

			case SETouchEnd:
				mPressedTouchCount -= mModifyTouchArray.size();
				(*start)->TouchesEnd( mModifyTouchArray.begin(), mModifyTouchArray.size(), button );
				break;
		}

		++start;
	}
	
	mModifyTouchArray.clear();
}

void SETouchController::EndTouching( SETouchType type )
{
	EndTouching( type, SETouchButtonNone );
}

int SETouchController::pressedTouchCount()
{
	return mPressedTouchCount;
}