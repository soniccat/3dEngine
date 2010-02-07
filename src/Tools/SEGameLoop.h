
#ifndef SEGameLoop_H
#define SEGameLoop_H


#include "SEGameLoopEngineInterface.h"
#include "SEIncludeLibrary.h"

class SEGameLoop;

typedef shared_ptr<SEGameLoop> SEGameLoopPtr;

class SEGameLoop
{
	static SEGameLoopPtr mInstance;
	SEGameLoopEngineInterfacePtr mEngine;

public:
	SEGameLoop(void);
	~SEGameLoop(void);

	static SEGameLoopPtr sharedInstance();
	void Run();
};

#endif SEGameLoop_H