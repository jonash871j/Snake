#pragma once
#include "Sprite.h"

class Scene : Import
{
private:
	char fileformat[3] = { 0 };
	char** mapPixelArray;
	int width, height;
	int cellWidth, cellHeight;

	//void DeleteArrays();

public:
	Sprite tileSprite = { 0, 0, 0 };
	std::vector<unsigned char> listID;

	Scene(int width, int height, int spriteWidth, int spriteHeight, int cellWidth, int cellHeight);
	Scene() {};
	// Used to import map
	void ImportMap(std::string filename);

	// *******************************
	void UpdatePixelArray();

	// Scene set section *********************************************
	
	// Used to set a character ID for a sprite in map
	void SetSpriteID(unsigned char charID, Sprite sprite);

	// Used to set tile precise in map
	void SetTilePrecise(int x, int y, unsigned char character);

	// Used to set tile in map
	void SetTile(int x, int y, unsigned char character);

	// Scene get section *********************************************

	inline unsigned char GetArray(int x, int y) const
	{
		if (x < 0) return NULL; if (y < 0) return NULL;
		if (x > width - 1) return NULL; if (y > height - 1) return NULL;
		return mapArray[y][x];
	}
	char GetFullArray readonly_2D mapPixelArray[y][x] rs
	
	// Scene property section ********************************************

	PROPERTY(float, Width);
	GET(Width) { return width; }

	PROPERTY(float, Height);
	GET(Height) { return height; }

	PROPERTY(float, CellWidth);
	GET(CellWidth) { return cellWidth; }

	PROPERTY(float, CellHeight);
	GET(CellHeight) { return cellHeight; }
};
