
#include "SETouchController.h"
#include "SEDefinition.h"


SETouchControllerPtr SETouchController::mInstance;

SETouchController::SETouchController(void)
{
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

void SETouchController::EndTouching( SETouchingType type )
{
	SEAssert( mModifyTouchArray.size(), "End not begin touch" );
	
	SETouchControllerDelegateArray::iterator start = mDelegateArray.begin();
	SETouchControllerDelegateArray::iterator end = mDelegateArray.end();

	while( start != end )
	{
		switch( type )
		{
			case SETouchingAddTouches:
				(*start)->TouchesBegin( mModifyTouchArray.begin(), mModifyTouchArray.size() );
				break;

			case SETouchingMoveTouches:
				(*start)->TouchesMove( mModifyTouchArray.begin(), mModifyTouchArray.size() );
				break;

			case SETouchingEndTouches:
				(*start)->TouchesEnd( mModifyTouchArray.begin(), mModifyTouchArray.size() );
				break;
		}

		++start;
	}
	
	mModifyTouchArray.clear();
}