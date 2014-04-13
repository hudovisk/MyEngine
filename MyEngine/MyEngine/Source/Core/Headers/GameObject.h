/*
 * GameObject.h
 *
 *  Created on: Apr 13, 2014
 *      Author: hudo
 */

#pragma once

#include "IRenderComponent.h"
#include "IController.h"

#include <memory>

class GameObject
{
public:
	GameObject() { }

	void attachRender(std::shared_ptr<IRenderComponent> render)
	{
		m_renderComponent = render;
	}

	void attachController(std::shared_ptr<IController> controller)
	{
		m_controller = controller;
	}

	void update()
	{
		if(m_controller)
		{
			m_controller->update();
		}
	}

	void render()
	{
		if(m_renderComponent)
		{
			m_renderComponent->draw();
		}
	}

private:
	std::shared_ptr<IRenderComponent> m_renderComponent;
	std::shared_ptr<IController> m_controller;
};
