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

	string backgorundImg, tmp, search, productField, reset;

	stream.open(CONFIG_FOLDER + "boardInit.txt");

    stream >> tmp >> backgorundImg;
	stream >> tmp >> m_searchBox.rect.x >> m_searchBox.rect.y >> m_searchBox.rect.w >> m_searchBox.rect.h;
	stream >> tmp >> search;
	stream >> tmp >> m_resetBox.rect.x >> m_resetBox.rect.y >> m_resetBox.rect.w >> m_resetBox.rect.h;
	stream >> tmp >> reset;
	stream >> tmp >> productField;

	stream.close();

	m_background = loadTexture(backgorundImg);

	loadZones();

	m_searchBox.texture = loadTexture(search);
	m_resetBox.texture = loadTexture(reset);

	loadProducts();

	m_productField.init(productField, "");
}

void Board::run()
{
	drawObject(m_background);

	drawObject(m_searchBox);
	drawObject(m_resetBox);

	drawZones();
	
	if (isMouseInRect(InputManager::m_mouseCoor, m_searchBox.rect) && InputManager::isMousePressed())
	{
		m_productToSearch = m_productField.getValue();

		toLower(m_productToSearch);

		searchProduct(m_productToSearch);
	}

	if (isMouseInRect(InputManager::m_mouseCoor, m_resetBox.rect) && InputManager::isMousePressed())
	{
		resetAll();
	}

	if (InputManager::isMousePressed())
	{
		if (isMouseInRect(InputManager::m_mouseCoor, m_productField.getRect()))
		{
			m_productField.readInput();
			world.m_inputManager.resetText(m_productField.getValue());
		}
		else
		{
			m_productField.stopInput();
		}
	}
	
	m_productField.setText(m_productField.getValue());
	m_productField.update();
	m_productField.draw();
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

	while (!stream.eof())
	{
		DrawableTwoTextures _zone;
		
		stream >> tmp >> _zone.rect.x >> _zone.rect.y >> _zone.rect.w >> _zone.rect.h;

		_zone.texture = loadTexture(NORMAL_FOLDER + tmp + ".bmp");

		_zone.texture2 = loadTexture(RED_FOLDER + tmp + "Red.bmp");

		_zone.copy = _zone.texture;

		m_zones.push_back(_zone);
	}

	stream.close();
}

void Board::loadProducts()
{
	fstream stream;

	string key;

	int value;

	stream.open(CONFIG_FOLDER + "products.txt");

	while (!stream.eof())
	{
		stream >> key >> value;

		m_products[key] = value;
	}

	stream.close();
}

void Board::changeTexture(DrawableTwoTextures& obj)
{
	SDL_Texture* tmp = obj.texture;
	obj.texture = obj.texture2;
	obj.texture2 = tmp;
}

void Board::searchProduct(string product)
{
	for (const auto& [key, value] : m_products) 
	{
		if (product == key)
		{
			changeTexture(m_zones[value - 1]);
		}
	}
}

void Board::resetAll()
{
	m_productField.setText("");

	for (int i = 0; i < m_zones.size(); i++)
	{
		m_zones[i].texture = m_zones[i].copy;
	}
}
