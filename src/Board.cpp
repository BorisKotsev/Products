#include "Board.h"
#include "Presenter.h"
#include "InputManager.h"
#include "SoundManager.h"

#include "World.h"

extern World world;

Board::Board()
{

}

Board::~Board()
{

}

void Board::init()
{
	fstream stream;

	string backgorundImg, tmp, search, productField, searchBox, exitBtn;

	stream.open(CONFIG_FOLDER + "boardInit.txt");

	stream >> tmp >> backgorundImg;
	stream >> tmp >> m_searchBox.rect.x >> m_searchBox.rect.y >> m_searchBox.rect.w >> m_searchBox.rect.h;
	stream >> tmp >> search;
	stream >> tmp >> productField;
	stream >> tmp >> searchBox;
	stream >> tmp >> exitBtn >> m_exitButton.rect.x >> m_exitButton.rect.y >> m_exitButton.rect.w >> m_exitButton.rect.h;

	stream.close();

	m_background = loadTexture(backgorundImg);
	m_exitButton.texture = loadTexture(exitBtn);

	loadZones();

	m_searchBox.texture = loadTexture(search);
	m_searchBoxText.texture = loadTexture(searchBox);

	loadProducts();
	loadDiscountProducts();

	m_productField.init(productField, "");
	m_searchBoxText.rect = m_productField.getRect();

	m_temp = m_searchBoxText.texture;
}

void Board::run()
{
	drawObject(m_background);
	drawObject(m_exitButton);

	if (isMouseInRect(InputManager::m_mouseCoor, m_exitButton.rect) && InputManager::isMousePressed())
	{
		world.m_stateManager.changeGameState(GAME_STATE::NONE);
	}

	drawZones();

	if (m_draw)
	{
		drawObject(m_searchBox);
	}

	if (m_canClick)
	{
		if ((isMouseInRect(InputManager::m_mouseCoor, m_searchBox.rect) && InputManager::isMousePressed() && m_draw) || 
			(isKeyPressed(SDL_SCANCODE_RETURN) && m_productField.getValue() != string(1, char(32))))
		{
			m_productToSearch = m_productField.getValue();

			if (m_productToSearch[0] == char(32))
			{
				m_productToSearch.erase(0, 1);
			}

			if (searchProduct(m_productToSearch) == -1)
			{
				m_popUp = new PopUp();

				m_popUp->init();

				m_canClick = false;
			}

			m_productField.stopInput();

			m_productField.setText(string(1, char(32)));

			changeTexture(m_searchBoxText);
		}
	}

	if (m_popUp != nullptr)
	{
		m_popUp->run();

		if (isMouseInRect(InputManager::m_mouseCoor, m_popUp->m_okButton) && InputManager::isMousePressed())
		{
			m_canClick = true;

			m_popUp->destroy();
			delete m_popUp;
			m_popUp = nullptr;
		}
	}

	if (m_canClick)
	{
		if (InputManager::isMousePressed())
		{
			if (isMouseInRect(InputManager::m_mouseCoor, m_productField.getRect()))
			{
				int tmp = searchProduct(m_productToSearch);
				resetAll();
				m_productField.setText(string(1, char(32)));
				changeTexture(m_searchBoxText);

				m_draw = true;
			
				m_productField.readInput();
				world.m_inputManager.resetText(m_productField.getValue());
			}
			else
			{
				m_productField.stopInput();
			}
		}
	}

	if (m_searchBoxText.texture == m_temp)
	{
		m_draw = false;
	}
	
	m_productField.setText(m_productField.getValue());
	m_productField.update();
	m_productField.draw();

	drawObject(m_searchBoxText);
}

void Board::drawZones()
{
	for (int i = 0; i < m_zones.size(); i++)
	{
		drawObject(m_zones[i]);
	}
}

void Board::destroy()
{
	SDL_DestroyTexture(m_background);

	m_productField.destroy();
}

void Board::loadZones()
{
	fstream stream;

	string tmp;

	stream.open(CONFIG_FOLDER + "zonesInfo.txt");

	DrawableTwoTextures _zone;

	while (!stream.eof())
	{
		stream >> tmp >> _zone.rect.x >> _zone.rect.y >> _zone.rect.w >> _zone.rect.h;

		_zone.texture = loadTexture(NORMAL_FOLDER + tmp + ".bmp");

		_zone.texture2 = loadTexture(RED_FOLDER + tmp + ".bmp");

		_zone.texture3 = loadTexture(YELLOW_FOLDER + tmp + ".bmp");

		_zone.copy = _zone.texture;

		m_zones.push_back(_zone);
	}

	stream.close();

	/*for(int i = 0; i < m_zones.size(); i++)
	{
		cout << i << " " << m_zones[i].rect.x << " " << m_zones[i].rect.y << " " << m_zones[i].rect.w << " " << m_zones[i].rect.h << endl;
		cout << i << " " << m_zones[i].texture << " " << m_zones[i].texture2 << " " << m_zones[i].texture3 << endl << endl;
	}

	cout << m_zones.size() << endl;*/
}

void Board::loadProducts()
{
	fstream stream;

	string key;

	int value;
	stream.open(CONFIG_FOLDER + "products.txt");

	while (stream >> value) 
	{
		getline(stream >> ws, key);

		key.erase(0, key.find_first_not_of(" \t\n\r"));
		key.erase(key.find_last_not_of(" \t\n\r") + 1);

		m_products[key] = value;
	}

	stream.close();

	/*for (const auto& product : m_products)
	{
		cout << "Key: " << product.first << ", Value: " << product.second << endl;
	}*/
}

void Board::loadDiscountProducts()
{
	fstream stream;

	string key;

	int value;
	stream.open(CONFIG_FOLDER + "discountProducts.txt");

	while (stream >> value)
	{
		getline(stream >> ws, key);

		key.erase(0, key.find_first_not_of(" \t\n\r"));
		key.erase(key.find_last_not_of(" \t\n\r") + 1);

		m_discountProducts[key] = value;
	}

	stream.close();

	/*for (const auto& product : m_discountProducts)
	{
		cout << "Key: " << product.first << ", Value: " << product.second << endl;
	}*/
}

void Board::changeTexture(DrawableTwoTextures& obj)
{
	SDL_Texture* tmp = obj.texture;
	obj.texture = obj.texture2;
	obj.texture2 = tmp;
}

void Board::changeDiscountTexture(DrawableTwoTextures& obj)
{
	SDL_Texture* tmp = obj.texture;
	obj.texture = obj.texture3;
	obj.texture3 = tmp;
}

int Board::searchProduct(string product)
{
	if(searchDiscountProduct(product) == 1)
	{
		return 1;
	}

	for (const auto& [key, value] : m_products)
	{
		if (product == key)
		{	
			changeTexture(m_zones[value - 1]);
			return 1;
		}
	}

	return -1;
}

int Board::searchDiscountProduct(string product)
{
	for (const auto& [key, value] : m_discountProducts)
	{
		if (product == key)
		{
			changeDiscountTexture(m_zones[value - 1]);
			return 1;
		}
	}

	return -1;
}

void Board::resetAll()
{
	for (int i = 0; i < m_zones.size(); i++)
	{
		m_zones[i].texture = m_zones[i].copy;
	}
}