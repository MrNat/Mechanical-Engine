//
//  main.m
//  Mechanical Engine App
//
//  Created by Nathan Hunt on 4/8/13.
//  Copyright (c) 2013 Bipolaron. All rights reserved.
//

#include "MechanicalCore.h"
#include "GameState.h"

int main(int argc, char *argv[])
{
	engineInit();
	engineOpenWindow(960, 540, "Mechanical Engine App");
	
	enginePushState(GameState::getInstance());
	engineMainLoop();
	
	engineTerminate();
	
	return 0;
}
