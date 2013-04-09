//
//  GameState.cpp
//  Mechanical Engine
//
//  Created by Nathan Hunt on 4/8/13.
//  Copyright (c) 2013 Bipolaron. All rights reserved.
//

#include "GameState.h"

#pragma mark Singleton

static GameState * _instance = NULL;

GameState::GameState()
{
	
}

GameState::~GameState()
{
	
}

GameState * GameState::getInstance(void)
{
	if (!_instance)
		_instance = new GameState();
	
	return _instance;
}


#pragma mark -
#pragma mark Init and Destroy

void GameState::init(void)
{
	// Draw triangle with VBO //
	const char* vertexSource =
	"#version 150\n"
	"in vec2 position;"
	"in vec3 color;"
	"out vec3 Color;"
	"void main() {"
	"	Color = color;"
	"	gl_Position = vec4( position, 0.0, 1.0 );"
	"}";
	/*
	const char* fragmentSource =
	"#version 150\n"
	"in vec3 Color;"
	"out vec4 outColor;"
	"void main() {"
	"	outColor = vec4( 1.0, 1.0, 1.0, 1.0 );"
	"}";
	 */
	
	GLuint vao;
	glGenVertexArrays( 1, &vao );
	glBindVertexArray( vao );
	
	GLuint vbo;
	glGenBuffers(1, &vbo);
	
	float vertices[] = {
		0.0f,  0.5f, // Vertex 1
		0.5f, -0.5f, // Vertex 2
		-0.5f, -0.5f  // Vertex 3
	};
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//const char * vertexSource = engineLoadFile("StandardShader.vert");
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);
	
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	const char * fragmentSource = engineLoadFile("shaders/StandardShader.frag");
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);
	
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glBindFragDataLocation(shaderProgram, 0, "outColor");
	glLinkProgram(shaderProgram);
	glUseProgram(shaderProgram);
	
	GLint posAttrib = glGetAttribLocation(shaderProgram, "position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	
	//c_string shader = engineLoadFile("shaders/StandardShader.vert");
	//printf("%s\n", shader);
}

void GameState::destroy(void)
{
	
}

#pragma mark -
#pragma mark Pause and Resume

void GameState::pause(void)
{
	
}

void GameState::resume(void)
{
	
}

#pragma mark -
#pragma mark Events

void GameState::handleEvent(void)
{
	// TODO: Add event support.
}

#pragma mark -
#pragma mark Updating and Rendering

void GameState::update(void)
{
	
}

void GameState::render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	
	glDrawArrays( GL_TRIANGLES, 0, 3 );
}


