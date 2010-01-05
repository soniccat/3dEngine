
#ifndef SEFileReaderBase_H
#define SEFileReaderBase_H

#include "SEIncludeLibrary.h"
#include "SEDefinition.h"
#include "SEError.h"


class SEPathBase;

class SEFileReaderHandlerInterface
{
public:
	virtual void HandleString(const sechar* string, bool isEndOfFile)=0;
}; 

typedef shared_ptr<SEFileReaderHandlerInterface> SEFileReaderHandlerInterfacePtr;
typedef vector< SEFileReaderHandlerInterfacePtr, SEAllocator<SEFileReaderHandlerInterfacePtr> > SEFileReaderHandlerInterfaceArray;


class SEFileReaderBase: public SEFileReaderHandlerInterface, public SEErrorInterface
{
protected:
	SEError error;

	sechar* mCurrentType;
	const SEPathBase* mCurrentFile;

	SEFileReaderHandlerInterface* mHandler;

public:
	SEFileReaderBase(void);
	virtual ~SEFileReaderBase(void);

	virtual void Load(const SEPathBase* filePath);
	virtual void Close();
	virtual void HandleString(const sechar* string, bool isEndOfFile);

	void SetHandler( SEFileReaderHandlerInterface* _handler );
	SEFileReaderHandlerInterface* handler();
};

typedef SEFileReaderBase SEFileReader;


#endif SEFileReaderBase_H
