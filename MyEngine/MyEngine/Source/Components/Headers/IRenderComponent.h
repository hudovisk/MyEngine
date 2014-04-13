/*
 * IRenderComponent.h
 *
 *  Created on: Apr 12, 2014
 *      Author: hudo
 */
#pragma once

class IRenderComponent
{
public:
	virtual ~IRenderComponent() { }

	virtual bool init() = 0;
	virtual bool destroy() = 0;
	virtual void draw() = 0;
};
