/*
 * Engine.h
 *
 *  Created on: Apr 3, 2014
 *      Author: hudo
 */

#pragma once

//#include "Input.h"
#include "../../../testPlayer.h"

namespace Engine
{
	enum EngineState
	{
		NOT_STARTED,

		RUNNING,
		PAUSED,
		EXITED,
	};
}

class IEngine
{
public:
	virtual ~IEngine() { }

	virtual bool init() = 0;
	virtual bool destroy() = 0;

	virtual void mainLoop() = 0;
};
