#include "Engine.h"
#include "Main.h"									

float hsp, vsp;
float speed = 2.0f;
int length = 0;
int xFruit, yFruit;
const int width = 28, height = 28;

Object objSnake(1, 2, 2);
Object objSnakeHead(1, 2, 2);
Object objFruit(1, 2, 2);
Sprite sprBorder(1, 4, 4);
Scene map(width, height, 2, 2, 2, 2);
Scene mapBorder(16, 16, 4, 4, 4, 4);

std::vector<int> xSnakeCoordinates(length), ySnakeCoordinates(length);

void DrawAll()
{
	Draw::Background(cFULL, BLACK);
	Draw::Rectangle(64, 0, SCREENWIDTH, SCREENHEIGHT, cFULL, D_BLUE, false);
	Draw::ScenePlain(mapBorder, 0, 0);
	Draw::ScenePlain(map, 4, 4);
	Draw::Text(fntNormal, 65, 1, "Snake", 0, Col(7, 1));
	Draw::Text(fntNormal, 65, 5, "v1.0b", 0, Col(8, 1));
	Draw::Text(fntNormal, 65, SCREENHEIGHT - 8, "Score", 0, Col(7, 1));
	Draw::Text(fntNormal, 65, SCREENHEIGHT - 4, length, 0, Col(WHITE, 1));
	Console::Update();
}

void InputKey()
{
	// Input
	if ((Input::KeyState(VK_RIGHT)) && (hsp == 0)) { hsp = 1; vsp = 0; }
	if ((Input::KeyState(VK_LEFT)) && (hsp == 0)) { hsp = -1; vsp = 0; }
	if ((Input::KeyState(VK_DOWN)) && (vsp == 0)) { hsp = 0; vsp = 1; }
	if ((Input::KeyState(VK_UP)) && (vsp == 0)) { hsp = 0; vsp = -1; }
}

void Logic()
{
	// Reset map
	for (int y = 0; y < SCREENHEIGHT; y++)
		for (int x = 0; x < SCREENWIDTH; x++)
			map.SetTile(x, y, ' ');

	// Update position
	int xPre = objSnake.XPos;
	int yPre = objSnake.YPos;
	objSnake.XPos += hsp;
	objSnake.YPos += vsp;

	// Border collision
	if (objSnake.XPos >= width) objSnake.XPos = 0;
	if (objSnake.XPos < 0) objSnake.XPos = width - 1;
	if (objSnake.YPos >= height) objSnake.YPos = 0;
	if (objSnake.YPos < 0) objSnake.YPos = height - 1;

	// Set fruit
	map.SetTile(xFruit, yFruit, 'f');

	// Check fruit
	if (map.GetArray(objSnake.XPos, objSnake.YPos) == 'f') {
		xFruit = Random(0, width - 1);
		yFruit = Random(0, height - 1);
		xSnakeCoordinates.push_back(0);
		ySnakeCoordinates.push_back(0);
		length++;
		Sound::Play("./Sound/point.wav");
	}

	// Set tail
	for (int i = 0; i < length; i++) {
		int xStore = xSnakeCoordinates[i];
		int yStore = ySnakeCoordinates[i];
		xSnakeCoordinates[i] = xPre;
		ySnakeCoordinates[i] = yPre;
		xPre = xStore;
		yPre = yStore;
		map.SetTile(xSnakeCoordinates[i], ySnakeCoordinates[i], '#');
	}

	// Check dead
	if (map.GetArray(objSnake.XPos, objSnake.YPos) == '#') {
		Sound::Play("./Sound/dead.wav");
		xSnakeCoordinates.clear();
		ySnakeCoordinates.clear();
		length = 0;
		objSnake.XPos = 13;
		objSnake.YPos = 13;
		cpSnake.FadeOut(1, 8);
		Logic();
		DrawAll();
		cpSnake.FadeIn(1, 8);
	}

	// Set head
	map.SetTile(objSnake.XPos, objSnake.YPos, '*');
}

void start()
{
	objSnake.sprite.ImportLayer("./Sprite/spr_snakePart", 0);
	objSnakeHead.sprite.ImportLayer("./Sprite/spr_snakeHead", 0);
	objFruit.sprite.ImportLayer("./Sprite/spr_fruit", 0);
	sprBorder.ImportLayer("./Sprite/spr_borderWall", 0);

	map.SetSpriteID('#', objSnake.sprite);
	map.SetSpriteID('*', objSnakeHead.sprite);
	map.SetSpriteID('f', objFruit.sprite);

	mapBorder.ImportMap("mapBorder");
	mapBorder.SetSpriteID(byte(219), sprBorder);

	Console::Create(85, 64);
	Console::SetFont(L"Lucida Console", 14, 14);
	Console::SetColorPalette(cpDefault);
	Console::SetWindowTitle("Snake");

	xFruit = Random(0, width - 1);
	yFruit = Random(0, height - 1);
	objSnake.XPos = 13;
	objSnake.YPos = 13;

	// Splash screen
	Console::SetColorPalette(cpDefault);
	Draw::SplashScreen(250);
	cpDefault.FadeOut(1, 4);
	Console::SetColorPalette(cpSnake);
}

void update()
{
	if (Input::KeyState(VK_ESCAPE)) terminateConsole = true;
	InputKey();
	Logic();
	DrawAll();
	Console::Delay(75);
}