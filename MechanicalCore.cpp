//
//  MechanicalCore.c
//  Mechanical Engine
//
//  Created by Nathan Hunt on 4/7/13.
//  Copyright (c) 2013 Bipolaron. All rights reserved.
//

#include "MechanicalCore.h"

static bool engineInitialized = false;
static bool engineWindowOpened = false;
static bool engineInMainLoop = false;

static vector<State *> states;

#pragma mark Main Engine Functions

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
		
		
		/*
		// This makes relative paths work in C++ in Xcode by changing directory to the Resources folder inside the .app bundle
#ifdef __APPLE__
		CFBundleRef mainBundle = CFBundleGetMainBundle();
		CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
		char path[PATH_MAX];
		if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
		{
			// error!
			printf("\nError changing resource directory.\n");
		}
		CFRelease(resourcesURL);
		
		chdir(path);
		//std::cout << "Current Path: " << path << std::endl;
#endif
		*/
		
		printf("done.\n");
	}
}


void engineTerminate(void)
{
	printf("Exiting...");
	
	while (!states.empty())
	{
		states.back()->destroy();
		states.pop_back();
	}
	
	glfwTerminate();
	exit(EXIT_SUCCESS);
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
		printf("Entering main loop...\n");
		engineInMainLoop = true;
		
		bool running = true;
		while (running)
		{
			if (!states.empty())
			{
				states.back()->update();
				states.back()->render();
			}
			
			glfwSwapBuffers();
			running = !glfwGetKey(GLFW_KEY_ESC) && glfwGetWindowParam(GLFW_OPENED);
		}
		
		engineTerminate();
	}
}

#pragma mark -
#pragma mark State Handling

void engineChangeState(State * newState)
{
	// Straight-up change scene immediately //
	if (!states.empty())
	{
		states.back()->destroy();
		states.pop_back();
	}
	
	states.push_back(newState);
	states.back()->init();
}

void enginePushState(State * newState)
{
	// Add the list, don't remove previous scene //
	if (!states.empty())
		states.back()->pause();
	
	states.push_back(newState);
	states.back()->init();
}

void enginePopState(State * newState)
{
	// Remove current state //
	if (!states.empty())
	{
		states.back()->destroy();
		states.pop_back();
	}
	
	// Resume previous state //
	if (!states.empty())
	{
		states.back()->resume();
	}
}

#pragma mark -
#pragma mark Loading Files & Shaders

char * engineLoadFile(const char * fileName)
{
	string data;
	std::ifstream fileStream(fileName, std::ios::in);
	if (fileStream.is_open())
	{
		string line = "";
		while (getline(fileStream, line))
			data += "\n" + line;
		fileStream.close();
	}
	else
	{
		printf("[Error] Cannot open %s.  Check file path.\n", fileName);
		return 0;
	}
	
	return (char *)data.c_str();
}

GLuint loadShaders(c_string vertexFilePath, c_string fragmentFilePath) // TODO: Create "loadFile" function elsewhere.
{
	
	// Create the Shaders //
	Shader vertexShader = glCreateShader(GL_VERTEX_SHADER);
	Shader fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	
	// Read Vertex Shader //
	string vertexShaderData; // Dump file into std::string
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
	if (vertexShaderStream.is_open())
	{
		string line = "";
		while (getline(vertexShaderStream, line))
			vertexShaderData += "\n" + line;
		vertexShaderStream.close();
	}
	else
	{
		printf("[ERROR] Cannot open %s.  Check file path.\n", vertexFilePath);
		return 0;
	}
	
	// Read Fragment Shader //
	string fragmentShaderData;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	if (fragmentShaderStream.is_open())
	{
		string line = "";
		while (getline(fragmentShaderStream, line))
			fragmentShaderData += "\n" + line;
		fragmentShaderStream.close();
	}
	else
	{
		printf("[Error] Cannot open %s.  Check file path.\n", fragmentFilePath);
		return 0;
	}
	
	GLint result = GL_FALSE;
	int infoLogLength;
	
	// Compile Shaders //
	c_string vertexShaderPointer = vertexShaderData.c_str();
	glShaderSource(vertexShader, 1, &vertexShaderPointer, NULL);
	glCompileShader(vertexShader);
	
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		vector<char> vertexShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(vertexShader, infoLogLength, NULL, &vertexShaderErrorMessage[0]);
		printf("%s\n", &vertexShaderErrorMessage[0]);
	}
	
	c_string fragmentShaderPointer = fragmentShaderData.c_str();
	glShaderSource(fragmentShader, 1, &fragmentShaderPointer, NULL);
	glCompileShader(fragmentShader);
	
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		vector<char> fragmentShaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(fragmentShader, infoLogLength, NULL, &fragmentShaderErrorMessage[0]);
		printf("%s\n", &fragmentShaderErrorMessage[0]);
	}
	
	// Link to the Program //
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	
	glGetProgramiv(program, GL_LINK_STATUS, &result);
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(program, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);
	}
	
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	return program;
	
	
}

