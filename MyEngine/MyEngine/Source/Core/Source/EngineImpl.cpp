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
	m_player(nullptr), m_window(nullptr), m_screenSurface(nullptr)
{
}

EngineImpl::~EngineImpl()
{
	destroy();
}

bool EngineImpl::destroy()
{
	m_eventManager->destroy();

	SDL_DestroyWindow( m_window );

	SDL_Quit();

	Logger::destroy();

	return true;
}

void SDLInitialization()
{

}

bool EngineImpl::init()
{
	Logger::init("log.txt",ALL);

	int status = SDL_Init(SDL_INIT_EVERYTHING);

	ASSERT(status != -1,"SDL init error: "<<SDL_GetError());

	m_window = SDL_CreateWindow( "My Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN );
	//Get window surface
	m_screenSurface = SDL_GetWindowSurface( m_window );
	//Fill the surface white
	SDL_FillRect( m_screenSurface, NULL, SDL_MapRGB( m_screenSurface->format, 0xFF, 0xFF, 0xFF ) );
	//Update the surface
	SDL_UpdateWindowSurface( m_window );
	LOG(INFO, "SDL initialized");
	m_eventManager = new EventManagerImpl();
	if(nullptr == m_eventManager || !m_eventManager->init())
	{
		ASSERT(false,"EventManager initialization error");
	}
	LOG(INFO, "Event Manager initialized");
	m_player = new Player();
	if(nullptr == m_player)
	{
		ASSERT(false,"Player initialization error");
		return false;
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
		m_player->update(updateTime);

		m_eventManager->dispatchEvents();

		auto now = high_resolution_clock::now();
		updateTime = static_cast<float>( (now - last).count() * duration::period::num ) / duration::period::den; //conversão da diferença para segundos.
		last = now;
	}
}

void EngineImpl::onWindowClosed(IEventDataPtr event)
{
	m_state = Engine::EXITED;
}



