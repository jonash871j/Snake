#pragma once
#include "Sprite.h"

class Font
{
private:
	int width, height;
	std::string folderPath, spritePath;
	Sprite fontSprite = { 0, 0, 0 };
public:
	Font(std::string folderPath, int width, int height);

	// Returns sprite path for current font character
	std::string GetSpritePath(char character);

	// Font property section ***************************************

	PROPERTY(int, Width);
	GET(Width) { return width; }

	PROPERTY(int, Height);
	GET(Height) { return height; }

	PROPERTY(Sprite, FontSprite);
	GET(FontSprite) { return fontSprite; }
};