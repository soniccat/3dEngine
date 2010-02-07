#include "SEGameLoop.h"
#include "SEGameLoopEngineConstantGameSpeedMaximumFPS.h"


SEGameLoopPtr SEGameLoop::mInstance;

SEGameLoop::SEGameLoop(void)
{
}

SEGameLoop::~SEGameLoop(void)
{
}

SEGameLoopPtr SEGameLoop::sharedInstance()
{
	if( mInstance.get() == 0 )
	{
		mInstance = SEGameLoopPtr( SENewObject<SEGameLoop>() );
	}

	return mInstance;
}

void SEGameLoop::Run()
{
	if( mEngine.get() == NULL )
	{
		mEngine = SEGameLoopEngineInterfacePtr( SENewObject<SEGameLoopEngineConstantGameSpeedMaximumFPS>() );
	}

	mEngine->Run();
}