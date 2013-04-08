//
//  MechanicalCore.c
//  Mechanical Engine
//
//  Created by Nathan Hunt on 4/7/13.
//  Copyright (c) 2013 Bipolaron. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "GLLibraries.h"

static bool engineInitialized = false;
static bool engineWindowOpened = false;
static bool engineInMainLoop = false;

void engineInit(void)
{
	if (engineInitialized)
	{
		// Engine already initialized //
		return;
	}
	else
	{
		printf("Engine initializing...");
		
		if (!glfwInit())
		{
			printf("failed.\n");
			printf("[ERROR] - Failed to init GLFW, check engineInit(), MechanicalCore.c");
			
			engineInitialized = true;
			exit(EXIT_FAILURE);
		}
		
		printf("done.\n");
	}
}

void engineOpenWindow(int windowWidth, int windowHeight, const char * title)
{
	if (engineWindowOpened)
	{
		// Window already opened. //
		return;
	}
	else
	{
		printf("Opening window...");
		
		// OpenGL 3.2 //
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
		glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
		glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		
		if (!glfwOpenWindow(windowWidth, windowHeight, 0, 0, 0, 0, 16, 0, GLFW_WINDOW))
		{
			printf("failed.\n");
			printf("[ERROR] - Failed to open GLFW window, check engineOpenWindow(), MechanicalCore.c");
			
			exit(EXIT_FAILURE);
		}
		
		// Edit Window Properties //
		glfwSetWindowTitle(title);
		glfwEnable(GLFW_STICKY_KEYS);
		glfwSwapInterval(1);
		glfwSetTime(0.0);
		
		// GLEW Init //
		glewExperimental = GL_TRUE;
		glewInit();
		
		// Draw a black screen //
		glClear(GL_COLOR_BUFFER_BIT);
		
		engineWindowOpened = true;
		printf("done.\n");
	}
}


void engineMainLoop(void)
{
	if (engineInMainLoop)
	{
		return;
	}
	else
	{
		printf("Entering main loop...");
		engineInMainLoop = true;
		
		bool running = true;
		while (running)
		{
			glfwSwapBuffers();
			running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
		}
	}
}


