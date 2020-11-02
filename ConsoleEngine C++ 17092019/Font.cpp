#include "Font.h"

Font::Font(std::string folderPath, int width, int height)
{
	Sprite sprite = { 1, width, height };
	this->fontSprite = sprite;
	this->folderPath = folderPath;
	this->width = width;
	this->height = height;
};

// Returns sprite path for current font character
std::string Font::GetSpritePath(char character)
{
	// Import numbers
	for (int i = 0; i < 255; i++) {
		if (character == char(i))
		{
			spritePath = folderPath + "fnt_" + char(i);
			//Exceptions
			switch (i){
				case char(32): spritePath = folderPath + "fnt_SPACE"; break;
			}
		}
	}
	return spritePath;
}