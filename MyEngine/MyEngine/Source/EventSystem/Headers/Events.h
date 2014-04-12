/*
 * Events.h
 *
 *  Created on: Apr 4, 2014
 *      Author: hudo
 */

#pragma once

#include <memory>


class IEventData;

typedef std::shared_ptr<IEventData> IEventDataPtr;

class IEventData
{
public:
	virtual ~IEventData() { }
	virtual const unsigned int getType() const = 0;
	virtual float getTimeStamp() const = 0;
//	virtual IEventData& copy() const = 0;
};

class BaseEventData : public IEventData
{
const float m_timeStamp;

public:
	BaseEventData(const float timeStamp = 0.0f) : m_timeStamp(timeStamp) { }

	// Returns the type of the event
	virtual const unsigned int getType() const = 0;

	float getTimeStamp(void) const { return m_timeStamp; }
};

class WindowClosedEventData : public BaseEventData
{
public:
	WindowClosedEventData(const float timeStamp = 0.0f) :
		BaseEventData(timeStamp)
	{

	}

	const unsigned int getType() const { return 0; }

//	IEventData& copy() const { return WindowClosedEventData(m_timeStamp);}
};
