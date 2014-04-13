/*
 * IController.h
 *
 *  Created on: Apr 13, 2014
 *      Author: hudo
 */

#pragma once

class IController
{
public:
	virtual ~IController() { }
	virtual void update() = 0;
};
