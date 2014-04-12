/*
 * EventManagerImpl.cpp
 *
 *  Created on: Apr 4, 2014
 *      Author: hudo
 */


#include <iostream>

#include "EventManagerImpl.h"
#include "Assert.h"
#include "Logger.h"

EventManagerImpl::EventManagerImpl()
{
}

/*
 * Assuming that SDL is already initialized!
 *
 * @todo: check for SDL initialization
 */
bool EventManagerImpl::init()
{
	/*
	 * Event Maps
	 */
	m_eventMap.insert( std::pair<unsigned int, GetIEventDataPtr>(SDL_WINDOWEVENT_CLOSE, [](const float timeStamp) -> IEventDataPtr
																			{
																				return IEventDataPtr(new WindowClosedEventData(timeStamp));
																			} ));

	/*
	 * Input Maps
	 */
	m_inputEventMap.insert( std::pair<unsigned int, InputEventType>(SDL_KEYDOWN, InputEventType::KEYBOARD) );
	m_inputEventMap.insert( std::pair<unsigned int, InputEventType>(SDL_KEYUP, InputEventType::KEYBOARD) );
	m_inputEventMap.insert( std::pair<unsigned int, InputEventType>(SDL_MOUSEMOTION, InputEventType::MOUSE) );
	m_inputEventMap.insert( std::pair<unsigned int, InputEventType>(SDL_MOUSEBUTTONDOWN, InputEventType::MOUSE) );
	m_inputEventMap.insert( std::pair<unsigned int, InputEventType>(SDL_MOUSEBUTTONUP, InputEventType::MOUSE) );
	m_inputEventMap.insert( std::pair<unsigned int, InputEventType>(SDL_MOUSEWHEEL, InputEventType::MOUSE) );
	return true;
}

/*
 * Assuming that SDL will be destroyed after, because it was already initialized
 *
 * @todo: check for SDL destroy
 */
bool EventManagerImpl::destroy()
{
	return true;
}

bool EventManagerImpl::dispatchEvents()
{
	SDL_Event event;
	IEventDataPtr p;
	while(SDL_PollEvent(&event) != 0)
	{
		translateSDLEvent(event);
	}

	for(auto itEvent = m_eventQueue.begin(); itEvent != m_eventQueue.end(); itEvent++)
	{
		auto itFind = m_mapEventListeners.find((*itEvent)->getType());
		if(itFind != m_mapEventListeners.end())
		{
			DelegateList& delegates = itFind->second;
			for(auto itDelegate = delegates.begin(); itDelegate != delegates.end(); itDelegate++)
			{
				(*itDelegate)(*itEvent);
			}
		}
	}

	m_eventQueue.clear();

	return m_eventQueue.empty();
}

void EventManagerImpl::translateSDLEvent(const SDL_Event& event)
{
	if(event.type == SDL_WINDOWEVENT)
	{
		auto itFind = m_eventMap.find(event.window.event);
		if(itFind != m_eventMap.end())
		{
			queueEvent(itFind->second(event.common.timestamp));
		}
	}
	else
	{
		auto itFind = m_inputEventMap.find(event.type);
		if(itFind != m_inputEventMap.end())
		{
			InputEvent inputEvent(event.common.timestamp);
			inputEvent.m_type = itFind->second;
			switch(inputEvent.m_type)
			{
				case InputEventType::KEYBOARD:
				{
					inputEvent.m_key = mapKeyInput(event);
					break;
				}
				case InputEventType::MOUSE:
				{
					inputEvent.m_mouse = mapMouseInput(event);
					break;
				}
				default:
				{
					ASSERT(false,"Unknown input type");
					break;
				}
			}

			if(m_inputQueue.size() >= MAX_INPUT_SIZE)
			{
				m_inputQueue.pop_front();
			}

			m_inputQueue.push_back(inputEvent);
		}
	}
}

bool EventManagerImpl::addListenner(const EventListenerDelegate& eventDelegate, const unsigned int type)
{
	DelegateList& delegates = m_mapEventListeners[type]; //find or create it
	for(auto it = delegates.begin(); it != delegates.end(); it++)
	{
		if(*it == eventDelegate)
		{
			LOG(WARN, "Double event listenner, type =  "<<type);
			return false;
		}
	}
	LOG(INFO, "Event Manager listenner added type = "<<type);
	delegates.push_back(eventDelegate);
	return true;
}

bool EventManagerImpl::removeListenner(const EventListenerDelegate& eventDelegate, const unsigned int type)
{
	auto itFind = m_mapEventListeners.find(type);
	if(itFind != m_mapEventListeners.end())
	{
		DelegateList& delegates = itFind->second;
		for(auto itDelegates = delegates.begin(); itDelegates != delegates.end(); itDelegates++)
		{
			if(*itDelegates == eventDelegate)
			{
				delegates.erase(itDelegates);
				LOG(INFO, "Event Manager listenner removed type = "<<type);
				return true;
			}
		}
	}
	LOG(WARN, "Fail to remove event listenner event type =  "<<type);
	return false;
}

bool EventManagerImpl::triggerEvent(const IEventDataPtr event) const
{
	auto itFind = m_mapEventListeners.find(event->getType());
	if(itFind != m_mapEventListeners.end())
	{
		const DelegateList& delegates = itFind->second;
		for(auto itDelegates = delegates.begin(); itDelegates != delegates.end(); itDelegates++)
		{
			(*itDelegates)(event);
		}
		LOG(INFO, "Event triggered type =  "<<event->getType());
		return true;
	}
	LOG(WARN, "Fail to trigger event type =  "<<event->getType());
	return false;
}

bool EventManagerImpl::queueEvent(const IEventDataPtr event)
{
	auto itFind = m_mapEventListeners.find(event->getType());
	if(itFind != m_mapEventListeners.end())
	{
		m_eventQueue.push_back(event);
		LOG(INFO, "Event queued type =  "<<event->getType());
		return true;
	}
	LOG(WARN, "Fail to queue event type =  "<<event->getType());
	return false;
}

bool EventManagerImpl::abortEvent(const unsigned int type)
{
	auto itFind = m_mapEventListeners.find(type);
	if(itFind != m_mapEventListeners.end())
	{
		for(auto itEvent = m_eventQueue.begin(); itEvent != m_eventQueue.end(); itEvent++)
		{
			if((*itEvent)->getType() == type)
			{
				m_eventQueue.erase(itEvent);
				LOG(INFO, "Event aborted type =  "<<type);
				return true;
			}
		}
	}
	LOG(WARN, "Fail to abort event type =  "<<type);
	return false;
}

KeyboardEvent EventManagerImpl::mapKeyInput(const SDL_Event& event) const
{
	KeyboardEvent key;
	key.m_code = event.key.keysym.sym;

	key.m_pressed = (event.type == SDL_KEYDOWN);

	return key;
}

MouseEvent EventManagerImpl::mapMouseInput(const SDL_Event& event) const
{
	MouseEvent mouse;
	if(event.type == SDL_MOUSEMOTION)
	{
		mouse.m_code = MOUSE_MOTION;
	}
	else
	{
		switch(event.button.button)
		{
			case SDL_BUTTON_LEFT:
			{
				mouse.m_code = MOUSE_BUTTON_LEFT;
				break;
			}
			case SDL_BUTTON_RIGHT:
			{
				mouse.m_code = MOUSE_BUTTON_RIGHT;
				break;
			}
			case SDL_BUTTON_MIDDLE:
			{
				mouse.m_code = MOUSE_BUTTON_MIDDLE;
				break;
			}
			case 4:
			{
				mouse.m_code = MOUSE_WHEEL_DOWN;
				break;
			}
			case 5:
			{
				mouse.m_code = MOUSE_WHEEL_UP;
				break;
			}
		}
		mouse.m_pressed = (event.type == SDL_MOUSEBUTTONDOWN);
	}

	mouse.m_posX = event.motion.x;
	mouse.m_posY = event.motion.y;

	return mouse;
}


