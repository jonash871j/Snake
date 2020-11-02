#include "ColorPalette.h"
#include "Console.h"

ColorPalette::ColorPalette() {};

ColorPalette::ColorPalette(std::string filename)
{
	ImportACCPAL(filename);
}

void ColorPalette::ImportColorPalette(std::string filename)
{
	ImportACCPAL(filename);
}

void ColorPalette::FadeOut(int delay, float speed)
{
	bool leave = false;
	float colorPaletteFade[16][3];
	for (int y = 0; y < 16; y++)
		for (int x = 0; x < 3; x++)
			colorPaletteFade[y][x] = (byte)colorPaletteArray[y][x];

	while (leave == false)
	{
		leave = true;
		for (int y = 0; y < 16; y++) {
			Console::SetColorRGB(y, byte(colorPaletteFade[y][0]), byte(colorPaletteFade[y][1]), byte(colorPaletteFade[y][2]));
			for (int x = 0; x < 3; x++) {
				if (colorPaletteFade[y][x] > 0) 
				{
					colorPaletteFade[y][x] -= speed;
					if (colorPaletteFade[y][x] <= 0) 
						colorPaletteFade[y][x] = 0;
					leave = false;
				}
			}
		}
	
		Console::Delay(delay);
		Console::Update();
	}
}

void ColorPalette::FadeIn(int delay, float speed)
{
	bool leave = false;
	float colorPaletteFade[16][3] = { 0 };

	while (leave == false)
	{
		leave = true;
		for (int y = 0; y < 16; y++) {
			Console::SetColorRGB(y, byte(colorPaletteFade[y][0]), byte(colorPaletteFade[y][1]), byte(colorPaletteFade[y][2]));
			for (int x = 0; x < 3; x++) {
				if (colorPaletteFade[y][x] < (byte)colorPaletteArray[y][x])
				{
					colorPaletteFade[y][x] += speed;
					if (colorPaletteFade[y][x] >= (byte)colorPaletteArray[y][x])
						colorPaletteFade[y][x] = (byte)colorPaletteArray[y][x];
					leave = false;
				}
			}
		}
		Console::Delay(delay);
		Console::Update();
	}
}
