/*
 * OpenGLRenderComponent.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: hudo
 */

#include "OpenGLRenderComponent.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include "Logger.h"

float vertices[] = {
            //Vertices according to faces
                -0.5f, -0.5f, 0.5f, //Vertex 0
                0.5f, -0.5f, 0.5f,  //v1
                -0.5f, 0.5f, 0.5f,  //v2
                0.5f, 0.5f, 0.5f,   //v3

                0.5f, -0.5f, 0.5f,  //...
                0.5f, -0.5f, -0.5f,
                0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, -0.5f,

                0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,

                -0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, 0.5f,
                -0.5f, 0.5f, -0.5f,
                -0.5f, 0.5f, 0.5f,

                -0.5f, -0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
                -0.5f, -0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,

                -0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, 0.5f,
                -0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                                    };

OpenGLRenderComponent::OpenGLRenderComponent() :
		m_program(0), m_vertexBuffer(0), m_vertexArray(0),
		m_vertices(nullptr), m_numVertices(0)
{

}

OpenGLRenderComponent::~OpenGLRenderComponent()
{
	destroy();
}

bool OpenGLRenderComponent::loadShaders(std::string vertexFilePath,std::string fragmentFilePath)
{
	//Create shaders
	GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);

	//Load vertex shader code
	std::stringstream vertexShaderStream;
	std::ifstream vertexShaderFile(vertexFilePath, std::ios::in);
	if(vertexShaderFile.is_open() == false)
	{
		LOG(ERROR, "Could not open vertex shader file: "<<vertexFilePath);
		return false;
	}
	vertexShaderStream << vertexShaderFile.rdbuf();
	vertexShaderFile.close();
	const std::string &vertexShaderSource = vertexShaderStream.str();
//	std::cout<<vertexShaderCode.str().c_str();

	//Load fragment shader code
	std::stringstream fragmentShaderStream;
	std::ifstream fragmentShaderFile(fragmentFilePath, std::ios::in);
	if(fragmentShaderFile.is_open() == false)
	{
		LOG(ERROR, "Could not open fragment shader file: "<<fragmentFilePath);
		return false;
	}
	fragmentShaderStream << fragmentShaderFile.rdbuf();
	fragmentShaderFile.close();
	const std::string &fragmentShaderSource = fragmentShaderStream.str();

//	std::cout<<fragmentShaderCode.str().c_str();

	int result = GL_FALSE;

	//Compile vertex shader
	const char* vertexSourcePointer = vertexShaderSource.c_str();
	int vertexSourceLenght = vertexShaderSource.length();
	glShaderSource(vertexShaderId, 1, &vertexSourcePointer, &vertexSourceLenght);
	glCompileShader(vertexShaderId);
	glGetShaderiv(vertexShaderId,GL_COMPILE_STATUS, &result);
	if(GL_FALSE == result)
	{
		int infoLogLenght = 0;
		glGetShaderiv(vertexShaderId, GL_INFO_LOG_LENGTH, &infoLogLenght);
		char* log = new char[infoLogLenght];
		glGetShaderInfoLog(vertexShaderId, infoLogLenght, NULL, log);
		LOG(ERROR,"Vertex shader compile error, "<<vertexFilePath<<" : "<<log);
		return false;
	}

	//Compile fragment shader
	char const * fragmentSourcePointer = fragmentShaderSource.c_str();
	int fragmentSourceLenght = fragmentShaderSource.length();
	glShaderSource(fragmentShaderId, 1, &fragmentSourcePointer, &fragmentSourceLenght);
	glCompileShader(fragmentShaderId);
	glGetShaderiv(fragmentShaderId,GL_COMPILE_STATUS, &result);
	if(GL_FALSE == result)
	{
		int infoLogLenght = 0;
		glGetShaderiv(fragmentShaderId, GL_INFO_LOG_LENGTH, &infoLogLenght);
		char* log = new char[infoLogLenght];
		glGetShaderInfoLog(fragmentShaderId, infoLogLenght, NULL, log);
		LOG(ERROR,"Fragment shader compile error, "<<fragmentFilePath<<" : "<<log);
		return false;
	}

	//Linking the program
	m_program = glCreateProgram();
	glAttachShader(m_program, vertexShaderId);
	glAttachShader(m_program, fragmentShaderId);
	glLinkProgram(m_program);

	glGetProgramiv(m_program, GL_LINK_STATUS, &result);
	if(GL_FALSE == result)
	{
		int infoLogLenght = 0;
		glGetProgramiv(m_program, GL_INFO_LOG_LENGTH, &infoLogLenght);
		char* log = new char[infoLogLenght];
		glGetProgramInfoLog(m_program, infoLogLenght, NULL, log);
		LOG(ERROR, "Compile shader error: "<<log);
		return false;
	}

	glDeleteShader(vertexShaderId);
	glDeleteShader(fragmentShaderId);

	return true;

}

bool OpenGLRenderComponent::init()
{
	m_vertices = vertices;
	m_numVertices = 24;

	if(!loadShaders("Shaders/vertex.glsl","Shaders/fragment.glsl"))
	{
		return false;
	}
	LOG(INFO,"Shaders loaded");

	glGenVertexArrays(1, &m_vertexArray);
	glBindVertexArray(m_vertexArray);

	glGenBuffers(1,&m_vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_numVertices*4*sizeof(float), m_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}


bool OpenGLRenderComponent::destroy()
{
	glDeleteBuffers(1, &m_vertexBuffer);
	glDeleteVertexArrays(1, &m_vertexArray);
	glDeleteProgram(m_program);

	return true;
}

void OpenGLRenderComponent::draw()
{
	glUseProgram(m_program);

	glBindVertexArray(m_vertexArray);

	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
	);

	// Draw the triangle !
	glDrawArrays(GL_TRIANGLE_STRIP, 0, m_numVertices); // 3 indices starting at 0 -> 1 triangle

	glDisableVertexAttribArray(0);

	glUseProgram(0);
}


