//
//  GameState.h
//  Mechanical Engine
//
//  Created by Nathan Hunt on 4/8/13.
//  Copyright (c) 2013 Bipolaron. All rights reserved.
//

#ifndef __Mechanical_Engine__GameState__
#define __Mechanical_Engine__GameState__

#include "MechanicalCore.h"

class GameState : public State
{
	
public:
	static GameState * getInstance(void);
	
	void init(void);
	void destroy(void);
	
	void pause(void);
	void resume(void);
	
	void handleEvent(void);
	void update(void);
	void render(void);
	
private:
	GameState();
	~GameState();
	
	// Private testing //
	//float vertices;
	
};

#endif /* defined(__Mechanical_Engine__GameState__) */
