#include "Draw.h"
#include "Input.h"

// Defitions used in the file only
#pragma region DEFINES
#define SPRITEMATRIX_START for (int y = 0; y < sprite.Height; y++){ \
								for (int x = 0; x < sprite.Width; x++) { \
									if (sprite.GetCharacterArray(x, y) != NULL)
#define SPRITEMATRIX_STOP }}
#define SPRITE sprite.GetCharacterArray(x, y), sprite.GetColorArray(x, y)
#define RX (-x + sprite.Width - 1)  // Current draw sprite x postion reversed
#define RY (-y + sprite.Height - 1) // Current draw sprite y postion reversed

#define X_OBJ xOff + object.XPos	 // Current draw object x postion
#define Y_OBJ yOff + object.YPos	 // Current draw object y postion

// Used to write character form array in diferent directions
#define SWITCH_WRITECHAR_DIRECTION switch (direction) {\
							       	case tLEFTRIGHT: Text(font, x + (i * (font.Width + 1)), y, charArray[i], color); break; \
							       	case tRIGHTLEFT: Text(font, x - (i * (font.Width + 1)), y, charArray[i], color); break; \
							       	case tTOPBUTTOM: Text(font, x, y + (i * (font.Height + 1)), charArray[i], color); break; \
							       	case tBUTTOMTOP: Text(font, x, y - (i * (font.Height + 1)), charArray[i], color); break; }

#define MAPMATRIX_START for (int y = 0; y < scene.Height; y++){ \
							for (int x = 0; x < scene.Width; x++)
#define MAPMATRIX_STOP }		            
#pragma endregion

// Draw font section *************************************************

// Used to draw a char with a font
void Draw::Text(Font font, int x, int y, char character, byte color)
{
	font.FontSprite.ImportLayer(font.GetSpritePath(character), 0);
	Draw::SpriteSingleColor(font.FontSprite, x, y, color);
}

// Used to draw a string with a font
void Draw::Text(Font font, int x, int y, std::string text, char direction, byte color)
{
	std::vector<char> charArray(text.begin(), text.end());
	charArray.push_back('\0');

	// Draw string to screen
	for (int i = 0; i < text.length(); i++)
		SWITCH_WRITECHAR_DIRECTION
}

// Used to draw a int with a font
void Draw::Text(Font font, int x, int y, int intValue, char direction, byte color)
{
	int intArrayLength = 0;
	std::vector <int> intArray = IntegerToArray(abs(intValue));
	std::vector <char> charArray(intArray.size());

	// If value is negative
	if (intValue < 0)
	{
		Text(font, x, y, '-', color);
		switch (direction) {
		case tLEFTRIGHT: x += font.Width + 1;  break;
		case tRIGHTLEFT: x -= font.Width + 1;  break;
		case tTOPBUTTOM: y += font.Height + 1; break;
		case tBUTTOMTOP: y -= font.Height + 1; break;
		}
	}
	// Draw int to screen
	for (int i = 0; i < intArray.size(); i++) {
		charArray[i] = intArray[i] + 48;
		SWITCH_WRITECHAR_DIRECTION
	}
}
// Draw premade scenes ***********************************************

// Used to draw splash screen
void Draw::SplashScreen(int duration)
{
	Sprite splash(1, 64, 32);
	splash.ImportLayer("./Sprite/spr_consoleSplashScreen", 0);
	for (int i = 0; i < duration; i++) {
		Draw::Background(219, BLACK);
		Draw::SpritePlain(splash, XMID - 28, YMID - 16);
		Console::WriteString(0, SCREENHEIGHT - 1, "v30.12.2019", 0, WHITE);
		Console::WriteString(SCREENWIDTH - 8, SCREENHEIGHT - 1, "BY JONAS", 0, WHITE);
		Console::Delay(1);
		Console::Update();
		if (Input::KeyPressed(VK_RETURN))
			return;
	}
}

// Draw scene section ************************************************

// Used to draw map of scene in full scale
void Draw::ScenePlain(Scene scene, int xOff, int yOff)
{
	MAPMATRIX_START
	{
		for (int i = 0; i < scene.listID.size(); i++) {
			if (scene.GetArray(x, y) == scene.listID[i]){
				scene.tileSprite.ChangeSpriteLayer(scene.listID[i]);
				Draw::SpritePlain(scene.tileSprite, (x * scene.CellWidth + xOff), (y * scene.CellHeight + yOff));
			}
		}
	}
	MAPMATRIX_STOP
}

// Used to draw map array of scene
void Draw::SceneArray(Scene scene, int xOff, int yOff, byte color)
{
	MAPMATRIX_START{ Console::WriteChar(x + xOff, y + yOff, scene.GetArray(x, y), color); }MAPMATRIX_STOP
}

// Draw sprite section ***********************************************

// Used to draw sprite
void Draw::SpritePlain(Sprite sprite, int xPos, int yPos)
{
	SPRITEMATRIX_START{ Console::WriteChar(x + xPos, y + yPos, SPRITE); }SPRITEMATRIX_STOP
}
void Draw::SpritePlain(Object object, int xOff, int yOff)
{ Draw::SpritePlain(object.sprite, X_OBJ, Y_OBJ);}

// Used to draw sprite that can flip and rotate
void Draw::SpriteDirection(Sprite sprite, int xPos, int yPos, bool flip, int rotation)
{
	SPRITEMATRIX_START
	{
		switch (flip)
		{
		case true:
			switch (rotation) {
			case 0: Console::WriteChar(x + xPos, y + yPos, SPRITE);     break;
			case 180: Console::WriteChar(RX + xPos, RY + yPos, SPRITE); break;
			case 90: Console::WriteChar(yPos + xPos, x + yPos, SPRITE); break;
			case 270: Console::WriteChar(y + yPos, RX + yPos, SPRITE);  break;
			}break;
		case false:
			switch (rotation) {
			case 0: Console::WriteChar(x + xPos, RY + yPos, SPRITE);    break;
			case 180: Console::WriteChar(RX + xPos, y + yPos, SPRITE);  break;
			case 90: Console::WriteChar(y + xPos, x + yPos, SPRITE);    break;
			case 270: Console::WriteChar(RY + xPos, RX + yPos, SPRITE); break;
			}break;
		}
	}
	SPRITEMATRIX_STOP
}
void Draw::SpriteDirection(Object object, int xOff, int yOff)
{ Draw::SpriteDirection(object.sprite, X_OBJ, Y_OBJ, object.Flip, object.Roation); }

// Used to draw sprite that only haves a single color
void Draw::SpriteSingleColor(Sprite sprite, int xPos, int yPos, byte color)
{
	SPRITEMATRIX_START{ Console::WriteChar(x + xPos, y + yPos, sprite.GetCharacterArray(x, y), color); }SPRITEMATRIX_STOP
}
void Draw::SpriteSingleColor(Object object, int xOff, int yOff, byte color)
{ Draw::SpriteSingleColor(object.sprite, X_OBJ, Y_OBJ, color); }

// Used to draw sprite that only haves a single character
void Draw::SpriteSingleCharacter(Sprite sprite, int xPos, int yPos, char character)
{
	SPRITEMATRIX_START{ Console::WriteChar(x + xPos, y + yPos, character, sprite.GetColorArray(x, y)); }SPRITEMATRIX_STOP
}
void Draw::SpriteSingleCharacter(Object object, int xOff, int yOff, char character)
{Draw::SpriteSingleCharacter(object.sprite, X_OBJ, Y_OBJ, character);}

// Used to draw sprite that only haves a single character and color
void Draw::SpriteShape(Sprite sprite, int xPos, int yPos, char character, byte color)
{
	SPRITEMATRIX_START{ Console::WriteChar(x + xPos, y + yPos, character, color); }SPRITEMATRIX_STOP
}
void Draw::SpriteShape(Object object, int xOff, int yOff, char character, byte color)
{Draw::SpriteShape(object.sprite, X_OBJ, Y_OBJ, character, color);}

// Used to draw a background with sprite
void Draw::SpriteBackground(Sprite sprite)
{
	for (int yB = 0; yB < ceil(SCREENHEIGHT / sprite.Height); yB++) {
		for (int xB = 0; xB < ceil(SCREENWIDTH / sprite.Width); xB++) {
			SPRITEMATRIX_START{
				Console::WriteChar(x + (xB * sprite.Width), y + (yB * sprite.Height), SPRITE);
			}SPRITEMATRIX_STOP
		}
	}
}

// Draw shape section ***********************************************

// Used to draw a background 
void Draw::Background(char character, byte color)
{
	for (int y = 0; y < SCREENHEIGHT; y++)
		for (int x = 0; x < SCREENWIDTH; x++)
			Console::WriteChar(x, y, character, color);
}

// Used to draw a rectanlge
void Draw::Rectangle(int x1, int y1, int x2, int y2, char character, byte color, bool outline)
{
	// Swap values if the first value is negative
	if (x2 < x1) std::swap(x2, x1);
	if (y2 < y1) std::swap(y2, y1);

	// Draw rectangle
	for (int y = y1; y <= y2; y++) {
		for (int x = x1; x <= x2; x++) {
			// Rectangle fill
			if (outline == false)
				Console::WriteChar(x, y, character, color);
			// Rectangle Outline
			else if ((x == x1) || (y == y1) || (x == x2) || (y == y2))
				Console::WriteChar(x, y, character, color);
		}
	}
}

// Used to draw a line
void Draw::Line(int x1, int y1, int x2, int y2, char character, byte color)
{
	// Calculation of Slope
	float ax = float(y2 - y1) / float(x2 - x1);
	float ay = float(x2 - x1) / float(y2 - y1);

	// Cordinate system
	int xp = x2 - x1, xm = -(x2 - x1);
	int yp = y2 - y1, ym = -(y2 - y1);
	int x, y;

	// Draw start- and end point
	Console::WriteChar(x1, y1, character, color);
	Console::WriteChar(x2, y2, character, color);

	// All drawing and calculation ///////////////////////////////////////////////////////////////
	// SLOPE AX																	/*      - ++++  */
	if ((xp >= ym) && (yp <= xp))												/*      -+++++  */
		for (x = 0; x < xp; x++)												/* -----O+++++  */
			Console::WriteChar(x1 + x, y1 + ax * x, character, color);			/*      -+++++  */
	else																		/*      - ++++  */
		// SLOPE -AY															/*    +++++     */
		if (ym >= xm)															/*     +++      */
			for (y = ym; y > 0; y--)											/* -----O------ */
				Console::WriteChar(x1 -(ay * y), y1 -y, character, color);		/*      -       */
		else																	/*      -       */
																				/* ++++ -       */
			// SLOPE -AX	 													/* +++++-       */
			if (yp <= xm)														/* +++++O------ */
				for (x = xm; x > 0; x--)										/* +++++-       */
					Console::WriteChar(x1 -x, y1 -(ax * x), character, color);	/* ++++ -       */
																				/*      -       */
			// SLOPE AY															/*      -       */
			else																/* -----O------ */
				for (y = 0; y < yp; y++)										/*     +++      */
					Console::WriteChar(x1 + ay * y, y1 + y, character, color);	/*    +++++     */
}

// 
void Draw::Triangle(int x1, int y1, int x2, int y2, int x3, int y3, char character, byte color)
{
	Draw::Line(x1, y1, x2, y2, character, color);														
	Draw::Line(x2, y2, x3, y3, character, color);														
	Draw::Line(x3, y3, x1, y1, character, color);														
}																										
																										
// Used to draw a circle																				
void Draw::Circle(int x, int y, int radius, char character, byte color)									
{																										
	int _x = 0;																							
	int _y = radius;																					
	int pi = 3 - 2 * radius;																			
	if (!radius)																						
		return;																							

	while (_y >= _x) // only formulate 1/8 of circle
	{
		Console::WriteChar(x - _x, y - _y, character, color); // Upper left left
		Console::WriteChar(x - _y, y - _x, character, color); // Upper upper left
		Console::WriteChar(x + _y, y - _x, character, color); // Upper upper right
		Console::WriteChar(x + _x, y - _y, character, color); // Upper right right
		Console::WriteChar(x - _x, y + _y, character, color); // Lower left left
		Console::WriteChar(x - _y, y + _x, character, color); // Lower lower left
		Console::WriteChar(x + _y, y + _x, character, color); // Lower lower right
		Console::WriteChar(x + _x, y + _y, character, color); // Lower right right
		if (pi < 0) pi += 4 * _x++ + 6;
		else pi += 4 * (_x++ - _y--) + 10;
	}
}