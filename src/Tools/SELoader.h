
#ifndef SELoader_H
#define SELoader_H


#include "SEIncludeLibrary.h"
#include "SELoaderDelegate.h"
#include "SEFileLineReader.h"

#define LOADER_BUFFER_SIZE 128


//executing string from file export in subclass
class SELoader: public SEFileReaderHandlerInterface
{
	SEFileLineReader mFileReader;
	SELoaderDelegateStack mDelegateStack;

	//buffers for delegates
	int mValidValueCount;

	sechar mDataType[LOADER_BUFFER_SIZE];
	sechar mValue1[LOADER_BUFFER_SIZE];
	sechar mValue2[LOADER_BUFFER_SIZE];
	sechar mValue3[LOADER_BUFFER_SIZE];
	int mCurrentIndex;

public:
	SELoader(void);
	~SELoader(void);

	virtual void Load(const SEPathBase* path);
	virtual void HandleString(const sechar* string, bool isEndOfFile);
	virtual void Close();

	void AddDelegate( SELoaderDelegatePtr loaderDelegatePtr );
	void PopDelegate( );

	int validValueCount() const;
	const sechar* dataType() const;
	const sechar* value1() const;
	const sechar* value2() const;
	const sechar* value3() const;

	void SetCurrentIndex( int value );
	int currentIndex();
};

#endif SELoader_H
