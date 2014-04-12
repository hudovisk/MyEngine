/*
 * EventManagerImpl.h
 *
 *  Created on: Apr 3, 2014
 *      Author: hudo
 */

#pragma once

#include <map>
#include <list>
#include <functional>

#include "IEventManager.h"
#include "InputTypes.h"
#include "SDL2/SDL.h"

class EventManagerImpl : public IEventManager
{
public:
	EventManagerImpl();

	bool init();
	bool destroy();

	bool dispatchEvents();

	/*
	 * Messages
	 */
	bool addListenner(const EventListenerDelegate& eventDelegate, const unsigned int type);
	bool removeListenner(const EventListenerDelegate& eventDelegate, const unsigned int type);

	bool triggerEvent(const IEventDataPtr event) const;
	bool queueEvent(const IEventDataPtr event);
	bool abortEvent(const unsigned int type);

	/*
	 * Inputs
	 */
	std::list<InputEvent>& getInputQueue() { return m_inputQueue; }

private:

	void translateSDLEvent(const SDL_Event& event);

	KeyboardEvent mapKeyInput(const SDL_Event& key) const;
	MouseEvent mapMouseInput(const SDL_Event& mouse) const;

	using DelegateList = std::list<EventListenerDelegate>;
	using EventListennersMap = std::map<unsigned int, DelegateList>;
	using GetIEventDataPtr = std::function<IEventDataPtr(const float)>;

	const unsigned int MAX_INPUT_SIZE = 100;

	/*
	 * Maps
	 */
	EventListennersMap m_mapEventListeners;
	std::map<unsigned int, GetIEventDataPtr> m_eventMap;
	std::map<unsigned int, InputEventType> m_inputEventMap;

	/*
	 * Queues
	 */
	std::list<InputEvent> m_inputQueue;
	std::list<IEventDataPtr> m_eventQueue;
};
