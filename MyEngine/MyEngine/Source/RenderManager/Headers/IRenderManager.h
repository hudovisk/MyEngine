/*
 * IRenderManager.h
 *
 *  Created on: Apr 12, 2014
 *      Author: hudo
 */

#pragma once

class IRenderManager
{
public:
	virtual ~IRenderManager() { }

	virtual void preRender() = 0;
	virtual void postRender() = 0;

	virtual bool init() = 0;
	virtual bool destroy() = 0;
};
