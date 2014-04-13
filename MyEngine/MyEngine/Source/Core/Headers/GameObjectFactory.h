/*
 * GameObjectFactory.h
 *
 *  Created on: Apr 13, 2014
 *      Author: hudo
 */

#pragma once

#include "GameObject.h"

class GameObjectFactory
{
public:
	static bool createPlayer(GameObject* player);
};
