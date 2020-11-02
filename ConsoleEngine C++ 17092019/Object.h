#pragma once
#include "Scene.h"

class Object
{
protected:
	float xPos = 0, yPos = 0;
	int roation = 0;
	bool flip = 0;

public:
	Sprite sprite = { 0, 0, 0 };

	Object(int spriteAmount, int width, int height);
	Object(Sprite sprite);
	Object();
	~Object();

	// Object events *************************************************

	// Returns true if this object collides with another object
	bool ObjectCollide(Object object, float xOff, float yOff);

	// Returns true if this object collides with a tile from a scene
	bool TileCollide(Scene scene, char tile);

	// Returns true if this object collides with a character of tile from a scene
	bool TilePreciseCollide(Scene scene, float xOff, float yOff, int xSizeOff, int ySizeOff, int tile);

	// Used to get distance to another object
	float ObjectDistance(Object object);

	// Object property section ********************************************

	PROPERTY(float, XPos);
	GET(XPos) { return xPos; }
	SET(XPos) { xPos = value; }

	PROPERTY(float, YPos);
	GET(YPos) { return yPos; }
	SET(YPos) { yPos = value; }

	PROPERTY(float, Flip);
	GET(Flip) { return flip; }
	SET(Flip) { flip = value; }

	PROPERTY(float, Roation);
	GET(Roation) { return roation; }
	SET(Roation) { roation = value; }
};