#include "PopUp.h"
#include "World.h"

PopUp::PopUp()
{

}

PopUp::~PopUp()
{

}

void PopUp::init()
{
	fstream stream;

	string tmp, popUpImg;

	stream.open(CONFIG_FOLDER + "popUp.txt");
	
	stream >> tmp >> popUpImg >> m_popUp.rect.x >> m_popUp.rect.y >> m_popUp.rect.w >> m_popUp.rect.h;
	stream >> tmp >> m_okButton.x >> m_okButton.y >> m_okButton.w >> m_okButton.h;
	
	stream.close();

	m_popUp.texture = loadTexture(popUpImg);
}  

void PopUp::run()
{
	drawObject(m_popUp);
}

void PopUp::destroy()
{
	SDL_DestroyTexture(m_popUp.texture);
}
