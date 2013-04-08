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
	glClearColor(0.0f, 0.2f, 0.8f, 1.0f);
}


