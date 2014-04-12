/*
 * IEventManager.h
 *
 *  Created on: Apr 3, 2014
 *      Author: hudo
 */

#pragma once

#include <map>
#include <list>
#include <tr1/memory>

#include "fastDelegate/delegate.hpp"
#include "Events.h"

typedef srutil::delegate1<void , IEventDataPtr> EventListenerDelegate;

class IEventManager
{
public:
	virtual ~IEventManager() { }

	virtual bool init() = 0;
	virtual bool destroy() = 0;

	virtual bool dispatchEvents() = 0;

	virtual bool addListenner(const EventListenerDelegate& eventDelegate, const unsigned int type) = 0;
	virtual bool removeListenner(const EventListenerDelegate& eventDelegate, const unsigned int type) = 0;

	virtual bool triggerEvent(const IEventDataPtr event) const = 0;
	virtual bool queueEvent(const IEventDataPtr event) = 0;
	virtual bool abortEvent(const unsigned int type) = 0;
};
