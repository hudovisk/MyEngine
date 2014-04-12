/*
 * InputContext.cpp
 *
 *  Created on: Apr 7, 2014
 *      Author: hudo
 */

#include <fstream>
#include <iostream>
#include <string>
#include <ctype.h>

#include "InputContext.h"
#include "Assert.h"

InputContext::InputContext()
{

}

bool InputContext::init(std::string filename)
{
	using namespace rapidxml;

	m_keyMap.clear();
	m_mouseMap.clear();

	std::ifstream file(filename, std::ios::ate);
	if(file.is_open())
	{
		unsigned int size = file.tellg();
		char* buffer = new char[size];
		if(buffer)
		{
			file.seekg(0,std::ios::beg);
			file.read(buffer,size);
//			std::cout<<"File:"<<std::endl<<buffer<<std::endl;
			xml_document<> doc;
			try
			{
				doc.parse<0>(buffer);
			}
			catch(parse_error& e)
			{
				file.close();
				ASSERT(false,"InputContext init file: "<<filename<<" error, possibly wrong file or bad XML. parser error: "<<e.what());
			}
			xml_node<>* root = doc.first_node();
//			std::cout<<"root node name: "<<root->name()<<std::endl;
			xml_node<>* node = root->first_node();
			while(node)
			{
				std::string name = node->name();
				if(name == "key")
				{
					m_keyMap.insert(mapXmlKeyNode(node));
				}
				else if(name == "mouse")
				{
					m_mouseMap.insert(mapXmlMouseNode(node));
				}
				else
				{
					ASSERT(false,"InputContext init file: "<<filename<<" error, node name: "<<name<<" not identified.");
				}
				node = node->next_sibling();
			}

			delete [] buffer;
			file.close();

			return true;
		}
	}
	file.close();

	return false;
}

InputContext::KeyMap InputContext::mapXmlKeyNode(rapidxml::xml_node<>* node)
{
	KeyMapAttributes keyAttributes;
//	unsigned int keyCode = static_cast<unsigned int> (*(node->first_attribute("value")->value()));
	unsigned int keyCode = tolower(*(node->first_attribute("value")->value()));
	keyAttributes.m_pressed = (strcasecmp(node->first_attribute("pressed")->value(),"true") == 0);
	keyAttributes.m_messageCode = atoi(node->first_attribute("message")->value());

	return KeyMap(keyCode,keyAttributes);
}
InputContext::MouseMap InputContext::mapXmlMouseNode(rapidxml::xml_node<>* node)
{
	MouseMapAttributes mouseAttributes;
	unsigned int mouseCode = 0;
	if(strcasecmp(node->first_attribute("value")->value(), "MOTION") == 0)
	{
		mouseCode = MOUSE_MOTION;
	}
	else if(strcasecmp(node->first_attribute("value")->value(), "BUTTON_LEFT") == 0)
	{
		mouseCode = MOUSE_BUTTON_LEFT;
	}
	else if(strcasecmp(node->first_attribute("value")->value(), "BUTTON_RIGHT") == 0)
	{
		mouseCode = MOUSE_BUTTON_RIGHT;
	}
	else if(strcasecmp(node->first_attribute("value")->value(), "BUTTON_MIDDLE") == 0)
	{
		mouseCode = MOUSE_BUTTON_MIDDLE;
	}
	else if(strcasecmp(node->first_attribute("value")->value(), "WHEEL_UP") == 0)
	{
		mouseCode = MOUSE_WHEEL_UP;
	}
	else if(strcasecmp(node->first_attribute("value")->value(), "WHEEL_DOWN") == 0)
	{
		mouseCode = MOUSE_WHEEL_DOWN;
	}
	else
	{
		ASSERT(false, "Incorrect mouse value: "<<node->first_attribute("value")->value());
	}
	mouseAttributes.m_pressed = (strcasecmp(node->first_attribute("pressed")->value(),"true") == 0);

	mouseAttributes.m_messageCode = atoi(node->first_attribute("message")->value());

	rapidxml::xml_node<>* nodeAxis = node->first_node("x");
	mouseAttributes.m_invertedX = (strcasecmp(nodeAxis->first_attribute("inverted")->value(),"true") == 0);

	nodeAxis = node->first_node("y");
	mouseAttributes.m_invertedY = (strcasecmp(nodeAxis->first_attribute("inverted")->value(),"true") == 0);

	return MouseMap(mouseCode,mouseAttributes);
}

std::vector<InputMessage> InputContext::parse(std::list<InputEvent>& input)
{
	std::vector<InputMessage> messages;
	for(auto itInput = input.begin(); itInput != input.end(); itInput++)
	{
		switch(itInput->m_type)
		{
			case InputEventType::KEYBOARD :
			{
				auto itFind = m_keyMap.find(itInput->m_key.m_code);
				if(itFind != m_keyMap.end())
				{
					KeyMapAttributes keyAttributes = itFind->second;
					if(itInput->m_key.m_pressed == keyAttributes.m_pressed)
					{
						InputMessage message;
						message.id = keyAttributes.m_messageCode;
						messages.push_back(message);
					}
					else
						std::cout<<"wrong key id"<<std::endl;
				}
				break;
			}
			case InputEventType::MOUSE :
			{
				auto itFind = m_mouseMap.find(itInput->m_mouse.m_code);
				if(itFind != m_mouseMap.end())
				{
					MouseMapAttributes mouseAttributes = itFind->second;
					InputMessage message;
					message.id = mouseAttributes.m_messageCode;
					message.pos[0] = (mouseAttributes.m_invertedX) ? -(itInput->m_mouse.m_posX) : itInput->m_mouse.m_posX;
					message.pos[1] = (mouseAttributes.m_invertedY) ? -(itInput->m_mouse.m_posY) : itInput->m_mouse.m_posY;
					messages.push_back(message);
				}
				break;
			}
			default:
			{

				break;
			}
		}
	}
	return messages;
}



