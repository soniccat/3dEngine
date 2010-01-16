
#ifndef SESceneLoader_H
#define SESceneLoader_H


#include "SEIncludeLibrary.h"
#include "SESceneLoaderDelegate.h"
#include "SEFileLineReader.h"

#define LOADER_BUFFER_SIZE 128


//executing string from file export in subclass
class SESceneLoader: public SEFileReaderHandlerInterface
{
	SEFileLineReader mFileReader;
	SESceneLoaderDelegateStack mDelegateStack;

	//buffers for delegates
	int mValidValueCount;

	sechar mDataType[LOADER_BUFFER_SIZE];
	sechar mValue1[LOADER_BUFFER_SIZE];
	sechar mValue2[LOADER_BUFFER_SIZE];
	sechar mValue3[LOADER_BUFFER_SIZE];
	int mCurrentIndex;
	const SEPathBase* mCurrentPath;

public:
	SESceneLoader(void);
	~SESceneLoader(void);

	virtual void Load(const SEPathBase* path);
	virtual void HandleString(const sechar* string, bool isEndOfFile);
	virtual void Close();

	void AddDelegate( SESceneLoaderDelegatePtr loaderDelegatePtr );
	void PopDelegate( );

	int validValueCount() const;
	const sechar* dataType() const;
	const sechar* value1() const;
	const sechar* value2() const;
	const sechar* value3() const;

	void SetCurrentIndex( int value );
	int currentIndex();
	const SEPathBase* currentPath(); 
};

#endif SESceneLoader_H
