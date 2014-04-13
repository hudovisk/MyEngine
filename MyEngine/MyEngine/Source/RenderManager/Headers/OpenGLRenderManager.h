/*
 * OpenGLRenderManager.h
 *
 *  Created on: Apr 12, 2014
 *      Author: hudo
 */

#pragma once

#include "IRenderManager.h"

#include "SDL2/SDL.h"
#include "GL/glew.h"

class OpenGLRenderManager : public IRenderManager
{
public:
	bool init();
	bool destroy();

	void preRender();
	void postRender();
private:
	SDL_Window* m_window;
	SDL_Surface* m_screenSurface;
};
