//
//  MechanicalCore.h
//  Mechanical Engine
//
//  Created by Nathan Hunt on 4/8/13.
//  Copyright (c) 2013 Bipolaron. All rights reserved.
//

#ifndef Mechanical_Engine_MechanicalCore_h
#define Mechanical_Engine_MechanicalCore_h

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <fstream>

#include "GLLibraries.h"
#include "EngineMacros.h"

#include "State.h"

// Main Engine Functions //
void engineInit(void);
void engineTerminate(void);
void engineOpenWindow(int windowWidth, int windowHeight, const char * title);
void engineMainLoop(void);

// State Handling //
void engineChangeState(State * newState);
void enginePushState(State * newState);
void enginePopState(void);

// Loading Files & Shaders //
char * engineLoadFile(c_string fileName);
GLuint engineLoadShader(c_string vertexFilePath, c_string fragmentFilePath);

#endif
