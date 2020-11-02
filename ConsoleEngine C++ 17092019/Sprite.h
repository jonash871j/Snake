#pragma once
#include "EngineCore.h"
#include "Import.h"

class Sprite : Import
{
private:
	char*** charcterLayerArray;
	char*** colorLayerArray;
	int spriteAmount;
	int width, height;

public:
	Sprite(int spriteAmount, int width, int height);
	~Sprite();

	// Sprite ********************************************************

	// Used to clean up sprite alocation and deconstruct sprite
	void DeleteAll();

	// Used to import a sprite into a sprite layer
	void ImportLayer(std::string filename, unsigned int spriteLayer);

	// Used to reaplce a sprite layer with another sprite
	void ReplaceLayer(unsigned int thisSpriteLayer, Sprite sprite, unsigned int spriteLayer);

	// Used to replace a sprite section layer with another sprite
	void ReplaceSectionLayer(int x1, int y1, int x2, int y2, unsigned int thisSpriteLayer, Sprite sprite, unsigned int spriteLayer);

	// Used to change sprite layer
	void ChangeSpriteLayer(unsigned int spriteLayer);

	char GetCharacterArray readonly_2D characterArray[y][x] rs
	char GetColorArray readonly_2D colorArray[y][x] rs

	// Sprite property section ***************************************
	PROPERTY(int, Width);
	GET(Width) { return width; }

	PROPERTY(int, Height);
	GET(Height) { return height; }
};

