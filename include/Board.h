#pragma once

#include "Engine.h"
#include "InputField.h"
#include "PopUp.h"

#include <string>
#include <algorithm>


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
	void loadDiscountProducts();
	void changeTexture(DrawableTwoTextures& obj);
	void changeDiscountTexture(DrawableTwoTextures& obj);

	vector <DrawableTwoTextures> m_zones;

	Drawable m_searchBox;
	Drawable m_exitButton;
	DrawableTwoTextures m_searchBoxText;

	map<string, int> m_products;
	map<string, int> m_discountProducts;

	InputField m_productField;

	string m_productToSearch;

	int searchProduct(string product);
	int searchDiscountProduct(string product);

	void resetAll();

	PopUp* m_popUp;

	bool m_draw = false;
	bool m_canClick = true;

	SDL_Texture* m_temp;
};