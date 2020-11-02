#pragma once
#include "Import.h"

class ColorPalette : Import
{
public:
	ColorPalette();
	ColorPalette(std::string filename);

	// Used to import colorpalette
	void ImportColorPalette(std::string filename);

	// Used to get value form the colorpalette, y[16] = colorID, x[3] = RGB
	char GetColorPalette readonly_2D colorPaletteArray[y][x] rs

	// Used to fade all colors to black
	void FadeOut(int delay, float speed);

	// Used to fade all colors to there normal
	void FadeIn(int delay, float speed);
};

