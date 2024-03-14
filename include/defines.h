#pragma once

#include <SDL_TTF.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <SDL.h>

using namespace std;

static string IMG_FOLDER = "img\\";
static string CONFIG_FOLDER = "config\\";
static string SOUND_FOLDER = "sound\\";
static string NORMAL_FOLDER = "normal\\";
static string RED_FOLDER = "red\\";
static string YELLOW_FOLDER = "yellow\\";
static string FONT_FOLDER = "ttf\\";

struct int2
{
	int x;
	int y;

	void reset()
	{
		x = 0;
		y = 0;
	}

	void set(int2 b) 
	{
		x = b.x;
		y = b.y;
	}

	void operator*=(int2 a)
	{
		x *= a.x;
		y *= a.y;
	}

	void operator/=(int2 a)
	{
		x /= a.x;
		y /= a.y;
	}

	int2 operator*(int2 a)
	{
		x *= a.x;
		y *= a.y;

		return *this; 
	}

	int2 operator/(int2 a)
	{
		x /= a.x;
		y /= a.y;

		return *this;
	}

	bool operator!=(int2 a)
	{
		if (x == a.x && y == a.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool operator==(int2 a)
	{
		if (x == a.x && y == a.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

struct float2
{
	float x;
	float y; 

	void reset()
	{
		x = 0;
		y = 0;
	}

	void set(float2 b)
	{
		x = b.x;
		y = b.y;
	}

	void operator*=(float2 a)
	{
		x *= a.x;
		y *= a.y;
	}

	void operator/=(float2 a)
	{
		x /= a.x;
		y /= a.y;
	}

	float2 operator*(float2 a)
	{
		x *= a.x;
		y *= a.y;

		return *this;
	}

	float2 operator/(float2 a)
	{
		x /= a.x;
		y /= a.y;

		return *this;
	}

	bool operator!=(float2 a)
	{
		if (x == a.x && y == a.y)
		{
			return false;
		}
		else
		{
			return true;
		}
	}

	bool operator==(float2 a)
	{
		if (x == a.x && y == a.y)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
};

enum class FONT
{
	NONE = 0,
	FONT = 1
};

enum class COLOR
{
	NONE = 0,
	LIGHT = 1,
	DARK = 2
};

struct Drawable 
{
	SDL_Texture* texture;
	SDL_Rect rect; //dstRect;
};

struct DrawableSrcRect : Drawable
{
	SDL_Rect srcRect;
};

struct DrawableTwoTextures : Drawable
{
	SDL_Texture* texture2;
	SDL_Texture* texture3;
	SDL_Texture* copy;
};

enum SOUND 
{
	BACKGORUND_MUSIC
};