#include "SEGameLoopEngineConstantGameSpeedMaximumFPS.h"
#include "SEPhysicWorld.h"

SEGameLoopEngineConstantGameSpeedMaximumFPS::SEGameLoopEngineConstantGameSpeedMaximumFPS(void)
{
}

SEGameLoopEngineConstantGameSpeedMaximumFPS::~SEGameLoopEngineConstantGameSpeedMaximumFPS(void)
{
}

void SEGameLoopEngineConstantGameSpeedMaximumFPS::Run()
{
	static const int TICKS_PER_SECOND = 50;
    static const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
    static const int MAX_FRAMESKIP = 10;
        
    static DWORD next_game_tick = GetTickCount();
    int loops;
    
	{
        loops = 0;
        while( GetTickCount() > next_game_tick && loops < MAX_FRAMESKIP)
		{
            SEPhysicWorld::sharedInstance()->world()->stepSimulation(1.0/25.0,1);
            
            next_game_tick += SKIP_TICKS;
            loops++;
        }
        
        SEPhysicWorld::sharedInstance()->Draw();
    }
}