#pragma once

class State
{
public:
	State();
	~State();
	
	// = 0
	virtual void init(); 

	virtual void run();

	virtual void destroy();
};