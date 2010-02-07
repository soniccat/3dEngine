
#ifndef SEGameLoopEngineConstantGameSpeedMaximumFPS_H
#define SEGameLoopEngineConstantGameSpeedMaximumFPS_H

#include "SEGameLoopEngineInterface.h"

//
//Realization of "Constant Game Speed with Maximum FPS"
//http://dewitters.koonsolo.com/gameloop.html
//
class SEGameLoopEngineConstantGameSpeedMaximumFPS: public SEGameLoopEngineInterface
{
public:
	SEGameLoopEngineConstantGameSpeedMaximumFPS(void);
	virtual ~SEGameLoopEngineConstantGameSpeedMaximumFPS(void);

	virtual void Run();
};


#endif SEGameLoopEngineConstantGameSpeedMaximumFPS_H