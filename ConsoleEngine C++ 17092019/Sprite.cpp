#include "Sprite.h"
#define SPRITEMATRIX_START for (int y = 0; y < height; y++){ \
						   for (int x = 0; x < width; x++)
#define MATRIX_STOP }

Sprite::Sprite(int spriteAmount, int width, int height)
{
	// Generates layer array
	charcterLayerArray = new char** [spriteAmount];
	for (int z = 0; z < spriteAmount; z++) {
		charcterLayerArray[z] = new char* [height];
		for (int y = 0; y < height; y++)
			charcterLayerArray[z][y] = new char[width];
	}
	colorLayerArray = new char** [spriteAmount];
	for (int z = 0; z < spriteAmount; z++) {
		colorLayerArray[z] = new char* [height];
		for (int y = 0; y < height; y++)
			colorLayerArray[z][y] = new char[width];
	}

	// Creates new chracter array for sprite
	characterArray = new char* [height];
	for (int i = 0; i < height; i++)
		characterArray[i] = new char[width];

	// Creates new color array for sprite
	colorArray = new char* [height];
	for (int i = 0; i < height; i++)
		colorArray[i] = new char[width];

	this->width = width;
	this->height = height;
	this->spriteAmount = spriteAmount;
};
Sprite::~Sprite() {};

void Sprite::DeleteAll()
{
	for (int z = 0; z < spriteAmount; z++) {
		for (int y = 0; y < height; y++) {
			delete[] charcterLayerArray[z][y];
			delete[] colorLayerArray[z][y];
		}
		delete[] charcterLayerArray[z];
		delete[] colorLayerArray[z];
	}
	delete[] charcterLayerArray;
	delete[] colorLayerArray;

	for (int y = 0; y < height; y++) {
		delete[] characterArray[y];
		delete[] colorArray[y];
	}
	delete[] characterArray;
	delete[] colorArray;
	Sprite::~Sprite();
}

// Used to import a sprite into a sprite layer
void Sprite::ImportLayer(std::string filename, unsigned int spriteLayer)
{
	// Checks if layer isn't out of bounds
	if (spriteLayer >= spriteAmount) return;

	ImportACXSPR(filename);

	// Sets layer array 
	SPRITEMATRIX_START{
	charcterLayerArray[spriteLayer][y][x] = characterArray[y][x];
	colorLayerArray[spriteLayer][y][x] = colorArray[y][x];
	}MATRIX_STOP
}

// Used to reaplce a sprite layer with another sprite
void Sprite::ReplaceLayer(unsigned int thisSpriteLayer, Sprite sprite, unsigned int spriteLayer)
{
	SPRITEMATRIX_START{
	charcterLayerArray[thisSpriteLayer][y][x] = sprite.charcterLayerArray[spriteLayer][y][x];
	colorLayerArray[thisSpriteLayer][y][x] = sprite.colorLayerArray[spriteLayer][y][x];
	}MATRIX_STOP
}

// Used to replace a sprite section layer with another sprite
void Sprite::ReplaceSectionLayer(int x1, int y1, int x2, int y2, unsigned int thisSpriteLayer, Sprite sprite, unsigned int spriteLayer)
{
	for (int y = y1; y < y2; y++) {
		for (int x = x1; x < x2; x++) {
			charcterLayerArray[thisSpriteLayer][y][x] = sprite.charcterLayerArray[spriteLayer][y][x];
			colorLayerArray[thisSpriteLayer][y][x] = sprite.colorLayerArray[spriteLayer][y][x];
		}
	}
}

// Used to change sprite layer
void Sprite::ChangeSpriteLayer(unsigned int spriteLayer)
{
	// Checks if layer isn't out of bounds
	if (spriteLayer > spriteAmount) return;

	SPRITEMATRIX_START{
		characterArray[y][x] = charcterLayerArray[spriteLayer][y][x];
		colorArray[y][x] = colorLayerArray[spriteLayer][y][x];
	}MATRIX_STOP
}