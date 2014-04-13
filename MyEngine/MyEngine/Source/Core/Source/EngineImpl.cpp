/*
 * Engine.cpp
 *
 *  Created on: Apr 3, 2014
 *      Author: hudo
 */

#include <chrono>

#include "EngineImpl.h"
#include "Assert.h"
#include "Logger.h"

EngineImpl::EngineImpl() :
	m_bInitialised(false), m_state(Engine::NOT_STARTED), m_eventManager(nullptr),
	m_renderManager(nullptr)
{
}

EngineImpl::~EngineImpl()
{
	destroy();
}

bool EngineImpl::destroy()
{
	m_eventManager->destroy();

	m_renderManager->destroy();

	Logger::destroy();

	return true;
}

void SDLInitialization()
{

}

bool EngineImpl::init()
{
	Logger::init("log.txt",ALL);

	m_renderManager = new OpenGLRenderManager();
	if(nullptr == m_renderManager || !m_renderManager->init())
	{
		ASSERT(false,"Render Manager initialization error");
	}
	LOG(INFO, "Render Manager initialized");



	m_eventManager = new EventManagerImpl();
	if(nullptr == m_eventManager || !m_eventManager->init())
	{
		ASSERT(false,"Event Manager initialization error");
	}
	LOG(INFO, "Event Manager initialized");



	if(!GameObjectFactory::createPlayer(&m_player))
	{
		ASSERT(false, "Player initialization error");
	}

	m_bInitialised = true;

	m_eventManager->addListenner(EventListenerDelegate::from_method<EngineImpl,&EngineImpl::onWindowClosed>(this),0);

	return m_bInitialised;
}

void EngineImpl::mainLoop()
{
	using std::chrono::high_resolution_clock;
	using duration = high_resolution_clock::duration;

	m_state = Engine::RUNNING;
	auto last = high_resolution_clock::now();
	float updateTime = 0;
	while(m_state == Engine::RUNNING)
	{
		m_player.update();

		m_eventManager->dispatchEvents();

		m_renderManager->preRender();

		m_player.render();

		m_renderManager->postRender();

		auto now = high_resolution_clock::now();
		updateTime = static_cast<float>( (now - last).count() * duration::period::num ) / duration::period::den; //conversão da diferença para segundos.
		last = now;
	}
}

void EngineImpl::onWindowClosed(IEventDataPtr event)
{
	m_state = Engine::EXITED;
}



