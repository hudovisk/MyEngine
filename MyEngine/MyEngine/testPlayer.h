/*
 * testPlayer.h
 *
 *  Created on: Mar 31, 2014
 *      Author: hudo
 */

#pragma once

#include <iostream>

//#include "InputManager.h"
#include "Vec3.h"

class Player
{
public:
	Player()
	{

	}

	bool initialise()
	{

//		if(nullptr == m_inputContext)
//		{
//			return false;
//		}
//		m_inputContext->addEventType(InputEventType::KEYBOARD);
//		m_inputContext->addEventType(InputEventType::MOUSE);

		return true;
	}

	void update(float dt)
	{
		m_pos = m_pos + m_velocity*dt;
	}

//	InputContext* getInputContext()
//	{
//		return m_inputContext;
//	}

private:
	Vec3 m_pos;
	Vec3 m_velocity;
//	InputContext* m_inputContext;

};

