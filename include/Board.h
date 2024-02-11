#pragma once

#include "Engine.h"
#include "InputField.h"
#include "PopUp.h"

class Board
{
public:
	Board();
	~Board();

	void init();
	void run();
	void drawZones();
	void destroy();

private:
	SDL_Texture* m_background;

	void loadZones();
	void loadProducts();
	void changeTexture(DrawableTwoTextures& obj);

	vector <DrawableTwoTextures> m_zones;

	Drawable m_searchBox;
	DrawableTwoTextures m_searchBoxText;

	map<string, int> m_products;

	InputField m_productField;

	string m_productToSearch;

	int searchProduct(string product);
	void resetAll();

	PopUp* m_popUp;

	bool m_draw = false;
};