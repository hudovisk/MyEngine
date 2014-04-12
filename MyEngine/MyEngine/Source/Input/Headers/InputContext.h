/*
 * InputContext.h
 *
 *  Created on: Mar 31, 2014
 *      Author: hudo
 */

#pragma once

#include <string>
#include <map>
#include <vector>
#include <list>
#include "InputTypes.h"
#include "rapidxml-1.13/rapidxml.hpp"

class InputMessage
{
public:
	unsigned int id;
	union
	{
		float value;
		float pos[2];
	};
};

class InputContext
{
public:
	InputContext();

	bool init(std::string filename);

	std::vector<InputMessage> parse(std::list<InputEvent>& input);
private:

	class MouseMapAttributes
	{
	public:
		unsigned int m_messageCode;
		bool m_invertedX;
		bool m_invertedY;
		bool m_pressed;
	};

	class KeyMapAttributes
	{
	public:
		unsigned int m_messageCode;
		bool m_pressed;
	};

	using KeyMap = std::pair<unsigned int, KeyMapAttributes>;
	using MouseMap = std::pair<unsigned int, MouseMapAttributes>;

	KeyMap mapXmlKeyNode(rapidxml::xml_node<>* node);
	MouseMap mapXmlMouseNode(rapidxml::xml_node<>* node);
	void setInvertedAxis(MouseMapAttributes& mouseAttribute, rapidxml::xml_node<>* node);

	std::map<unsigned int, KeyMapAttributes> m_keyMap;
	std::map<unsigned int, MouseMapAttributes> m_mouseMap;
	//joystick map
};

