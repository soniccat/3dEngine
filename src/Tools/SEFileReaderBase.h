
#ifndef SEFileReaderBase_H
#define SEFileReaderBase_H

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEError.h"


class SEPathBase;

class SEFileReaderDelegate
{
public:
	virtual void HandleString(const sechar* string, bool isEndOfFile)=0;
}; 

typedef shared_ptr<SEFileReaderDelegate> SEFileReaderDelegatePtr;
typedef vector< SEFileReaderDelegatePtr, SEAllocator<SEFileReaderDelegatePtr> > SEFileReaderDelegateArray;


class SEFileReaderBase: public SEFileReaderDelegate, public SEErrorInterface
{
protected:
	SEError error;

	sechar* mCurrentType;
	const SEPathBase* mCurrentFile;

	SEFileReaderDelegate* mDelegate;

public:
	SEFileReaderBase(void);
	virtual ~SEFileReaderBase(void);

	virtual void Load(const SEPathBase* filePath);
	virtual void Close();
	virtual void HandleString(const sechar* string, bool isEndOfFile);

	void SetDelegate( SEFileReaderDelegate* _delegate );
	SEFileReaderDelegate* delegate();
};

typedef SEFileReaderBase SEFileReader;


#endif SEFileReaderBase_H
