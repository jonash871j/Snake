#include "Scene.h"

Scene::Scene(int width, int height, int spriteWidth, int spriteHeight,int cellWidth, int cellHeight)
{
	this->cellWidth = cellWidth;
	this->cellHeight = cellHeight;
	this->width = width;
	this->height = height;

	// Defines the size of the sprites in sprite array
	Sprite tileSprite = { 255, spriteWidth, spriteHeight };
	this->tileSprite = tileSprite;

	// Defines the size of the map arrays
	mapArray = new char* [height];
	for (int i = 0; i < height; i++)
		mapArray[i] = new char[width];

	// Defines the size of the pixel arrays
	int mapPixelWidth = (width * cellWidth) + 1;
	int mapPixelHeight = (height * cellHeight) + 1;
	mapPixelArray = new char* [mapPixelHeight];
	for (int i = 0; i < mapPixelHeight; i++)
		mapPixelArray[i] = new char[mapPixelWidth];
}

// Private - Delete arrays
//void Scene::DeleteArrays()
//{
//	for (int i = 0; i < cellHeight; i++)
//		delete[] mapArray[i];
//	delete[] mapArray;
//}

// Used to import map
void Scene::ImportMap(std::string fileName)
{ 
	ImportMAP(fileName);
}

// Updating pixel array
void Scene::UpdatePixelArray()
{
	for (int yh = 0; yh < height; yh++)
		for (int xw = 0; xw < width; xw++)
			for (int yc = 0; yc < cellHeight; yc++)
				for (int xc = 0; xc < cellWidth; xc++)
					mapPixelArray[yc + (yh * cellHeight)][xc + (xw * cellWidth)] = mapArray[yh][xw];
}

// Used to set a character ID for a sprite in map
void Scene::SetSpriteID(unsigned char charId, Sprite sprite)
{
	tileSprite.ReplaceLayer(charId, sprite, 0);
	listID.push_back(charId);
}

// Used to set tile precise in map
void Scene::SetTilePrecise(int x, int y, unsigned char character)
{
	for (int yc = 0; yc < cellHeight; yc++)
		for (int xc = 0; xc < cellWidth; xc++)
			mapArray[int(y + yc) / cellHeight][int(x + xc) / cellWidth] = character;
}

// Used to set tile in map
void Scene::SetTile(int x, int y, unsigned char character)
{
	if ((x >= 0) && (x < width) && (y >= 0) && (y < height))
		mapArray[y][x] = character;
}
