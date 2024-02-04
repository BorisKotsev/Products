#pragma once

#include "Engine.h"

class PopUp
{
public:
	PopUp();
	~PopUp();

	void init();
	void run();
	void destroy();
	
	SDL_Rect m_okButton;

private:
	Drawable m_popUp;
};