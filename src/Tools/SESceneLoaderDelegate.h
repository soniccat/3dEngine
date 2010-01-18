
#ifndef SESceneLoaderDelegate_H
#define SESceneLoaderDelegate_H


class SESceneLoader;

class SESceneLoaderDelegate
{
public:
	virtual void ParseData( SESceneLoader* loader )=0;
};

typedef shared_ptr<SESceneLoaderDelegate> SESceneLoaderDelegatePtr;
typedef vector<SESceneLoaderDelegatePtr, SEAllocator<SESceneLoaderDelegatePtr> > SESceneLoaderDelegateArray;
typedef stack< SESceneLoaderDelegatePtr, SESceneLoaderDelegateArray> SESceneLoaderDelegateStack;


#endif SESceneLoaderDelegate_H