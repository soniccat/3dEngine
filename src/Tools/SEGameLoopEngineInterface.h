
#ifndef SEGameLoopEngineInterface_H
#define SEGameLoopEngineInterface_H

#include "SEIncludeLibrary.h"

class SEGameLoopEngineInterface;

typedef shared_ptr<SEGameLoopEngineInterface> SEGameLoopEngineInterfacePtr;

class SEGameLoopEngineInterface
{
public:
	SEGameLoopEngineInterface(void);
	virtual ~SEGameLoopEngineInterface(void);

	virtual void Run()=0;
};


#endif SEGameLoopEngineInterface_H