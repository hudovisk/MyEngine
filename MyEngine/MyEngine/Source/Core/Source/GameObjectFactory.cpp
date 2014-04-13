/*
 * GameObjectFactory.cpp
 *
 *  Created on: Apr 13, 2014
 *      Author: hudo
 */

#include "GameObjectFactory.h"
#include "OpenGLRenderComponent.h"

bool GameObjectFactory::createPlayer(GameObject* player)
{
	std::shared_ptr<IRenderComponent> render(new OpenGLRenderComponent);
	if(!render->init())
	{
		return false;
	}

	player->attachRender(render);

	return true;
}


