
#ifndef SELoaderDelegate_H
#define SELoaderDelegate_H


class SELoader;

class SELoaderDelegate
{
public:
	virtual void ParseData( SELoader* loader )=0;
};

typedef shared_ptr<SELoaderDelegate> SELoaderDelegatePtr;
typedef vector<SELoaderDelegatePtr, SEAllocator<SELoaderDelegatePtr> > SELoaderDelegateArray;
typedef stack< SELoaderDelegatePtr, SELoaderDelegateArray> SELoaderDelegateStack;


#endif SELoaderDelegate_H