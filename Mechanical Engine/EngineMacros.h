//
//  EngineMacros.h
//  Mechanical Engine
//
//  Created by Nathan Hunt on 4/8/13.
//  Copyright (c) 2013 Bipolaron. All rights reserved.
//

#ifndef Mechanical_Engine_EngineMacros_h
#define Mechanical_Engine_EngineMacros_h

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <math.h>

#ifdef __APPLE__
  #include "CoreFoundation/CoreFoundation.h"
#endif


// String Types //
typedef const char * c_string;
typedef std::string string;

// Vector //
template <class T>
using vector = std::vector<T>;

// Shaders //
typedef GLuint Shader;

#endif
