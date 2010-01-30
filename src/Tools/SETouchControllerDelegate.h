
#ifndef SETouchControllerDelegate_H
#define SETouchControllerDelegate_H

#include "SEIncludeLibrary.h"
#include "SETouch.h"

class SETouchControllerDelegate;

typedef shared_ptr<SETouchControllerDelegate> SETouchControllerDelegatePtr;
typedef vector<SETouchControllerDelegatePtr> SETouchControllerDelegateArray;


class SETouchControllerDelegate
{
public:
	SETouchControllerDelegate(void);
	~SETouchControllerDelegate(void);

	virtual void TouchesBegin( SETouchArray::iterator touch, size_t count );
	virtual void TouchesMove( SETouchArray::iterator touch, size_t count );
	virtual void TouchesEnd( SETouchArray::iterator touch, size_t count );
};


#endif SETouchControllerDelegate_H
