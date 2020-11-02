#pragma once
#include "EngineCore.h"
#include "ColorPalette.h"

namespace Console
{
	// Console general section ******************************************

	// Used to start the console engine and set screen dimensions
	void Create(short screenWidth, short screenHeight);

	// Used to update the console
	void Update();

	// Used to destroy the console engine
	void Destroy();

	// Console write section ********************************************

	// Used to write a character to the console
	void WriteChar(int x, int y, char character, byte color);

	// Used to write a string to the console
	void WriteString(int x, int y, std::string text, char direction, byte color);

	// Used to write a int to the console
	void WriteInt(int x, int y, int intValue, char direction, byte color);

	// Console set section **********************************************

	// Used to set the console font
	void SetFont(const wchar_t* fontType, char fontSizeX, char fontSizeY);

	// Used to set a color palette for the console
	void SetColorPalette(ColorPalette colorPalette);

	// Used to set a RGB color for a color id in the console
	void SetColorRGB(char id, byte red, byte green, byte blue);

	// Used to set the window title for the console
	void SetWindowTitle(std::string text);

	// Console get section **********************************************

	// Returns Frames Per Second
	float GetFPS();

	// Returns screen width
	int GetScreenWidth();

	// Returns screen height
	int GetScreenHeight();

	// Delays console
	void Delay(int delay);
}


#define SCREENWIDTH Console::GetScreenWidth()
#define SCREENHEIGHT Console::GetScreenHeight()
#define XMID SCREENWIDTH / 2
#define YMID SCREENHEIGHT / 2