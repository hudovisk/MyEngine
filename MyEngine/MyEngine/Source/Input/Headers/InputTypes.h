/*
Input types definition
created: 30/03/2014
last modified: 
author: Hudo
*/

#pragma once

#include "SDL2/SDL_keycode.h"

enum class InputEventType
{
	UNKNOWN,
	KEYBOARD,
	MOUSE,
};

enum MouseCode
{
	MOUSE_MOTION,

	MOUSE_BUTTON_LEFT,
	MOUSE_BUTTON_RIGHT,
	MOUSE_BUTTON_MIDDLE,
	MOUSE_WHEEL_UP,
	MOUSE_WHEEL_DOWN,
};

class KeyboardEvent
{
public:
	SDL_Keycode m_code;
	bool m_pressed;
};

class MouseEvent
{
public:
	MouseCode m_code;
	int m_posX;
	int m_posY;
	bool m_pressed;
};

class InputEvent
{
public:
	InputEvent(const float timeStamp)
		: m_type(InputEventType::UNKNOWN), m_timeStamp(timeStamp)
	{

	}

	InputEventType m_type;
	const float m_timeStamp;

	KeyboardEvent m_key;
	MouseEvent m_mouse;
};

