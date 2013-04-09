//
//  State.h
//  Mechanical Engine
//
//  Created by Nathan Hunt on 4/8/13.
//  Copyright (c) 2013 Bipolaron. All rights reserved.
//

#ifndef __Mechanical_Engine__State__
#define __Mechanical_Engine__State__

class State
{
public:
	virtual void init(void) = 0;
	virtual void destroy(void) = 0;
	
	virtual void pause(void) = 0;
	virtual void resume(void) = 0;
	
	virtual void handleEvent(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;
};

#endif /* defined(__Mechanical_Engine__State__) */
