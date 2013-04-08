//
//  main.cpp
//  Mechanical Engine
//
//  Created by Nathan Hunt on 4/7/13.
//  Copyright (c) 2013 Bipolaron. All rights reserved.
//

#include "MechanicalCore.h"

//#include "MenuState.h"
#include "GameState.h"

int main(int argc, const char * argv[])
{
	engineInit();
	engineOpenWindow(960, 540, "Mechanical Engine");
	
	enginePushState(GameState::getInstance());
	engineMainLoop();
	
	engineTerminate();
	
	return 0;
}

