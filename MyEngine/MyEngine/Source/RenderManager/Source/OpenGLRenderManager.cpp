/*
 * OpenGLRenderManager.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: hudo
 */

#include "OpenGLRenderManager.h"
#include "Assert.h"
#include "Logger.h"

bool OpenGLRenderManager::init()
{
	int status = SDL_Init(SDL_INIT_EVERYTHING);

	if(status == -1)
	{
		LOG(ERROR, "SDL init error: "<<SDL_GetError());
		return false;
	}

	m_window = SDL_CreateWindow( "My Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	//Get window surface
	m_screenSurface = SDL_GetWindowSurface( m_window );
	//Fill the surface white
	SDL_FillRect( m_screenSurface, NULL, SDL_MapRGB( m_screenSurface->format, 0xFF, 0xFF, 0xFF ) );
	//Update the surface
	SDL_UpdateWindowSurface( m_window );
	LOG(INFO, "SDL initialized");

	GLenum err = glewInit();
	if(GLEW_OK != err)
	{
		LOG(ERROR, "GLew initialization error: "<<glewGetErrorString(err));
		return false;
	}
	LOG(INFO,"GLEW initialized");

	glClearColor(0, 0, 0, 1); // black

	return true;
}

bool OpenGLRenderManager::destroy()
{
	SDL_DestroyWindow( m_window );

	SDL_Quit();
}

void OpenGLRenderManager::preRender()
{
	//CLEAR
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void OpenGLRenderManager::postRender()
{
	//SWAP BUFFERS
	SDL_GL_SwapWindow(m_window);
}



