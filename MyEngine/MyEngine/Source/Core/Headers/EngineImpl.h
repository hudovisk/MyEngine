/*
 * EngineImpl.h
 *
 *  Created on: Apr 4, 2014
 *      Author: hudo
 */

#pragma once

#include "IEngine.h"
#include "GameObjectFactory.h"
#include "EventManagerImpl.h"
#include "OpenGLRenderManager.h"

#include "../../../testPlayer.h"

class EngineImpl : public IEngine
{
public:
	EngineImpl();
	~EngineImpl();

	bool init();
	bool destroy();

	void mainLoop();

	void onWindowClosed(IEventDataPtr event);
private:
	bool m_bInitialised;
	Engine::EngineState m_state;

	IEventManager* m_eventManager;
	IRenderManager* m_renderManager;

	GameObject m_player;
};
