/*
 * OpenGLRenderComponent.h
 *
 *  Created on: Apr 12, 2014
 *      Author: hudo
 */

#include "GL/glew.h"
#include <vector>
#include <string>

#include "IRenderComponent.h"

class OpenGLRenderComponent : public IRenderComponent
{
public:
	OpenGLRenderComponent();
	~OpenGLRenderComponent();

	bool init();
	bool destroy();
	void draw();

private:
	bool loadShaders(std::string vertexFilePath,std::string fragmentFilePath);

	GLuint m_program;
	GLuint m_vertexBuffer;
	GLuint m_vertexArray;

	float* m_vertices;
	unsigned int m_numVertices;
};


