#pragma once
#include "Console.h"

namespace Input
{
	// Returns true if keystate is true
	bool KeyState(int key);

	// Input key hold delayed loop
	bool KeyStateDelayedLoop(int key);

	// Returns true if keystate is true and after the delay
	bool KeyStateDelayed(int key, int delay);

	// Returns true if key is pressed
	bool KeyPressed(int key);

	// Returns true if key is released
	bool KeyReleased(int key);

	// Used to press key with code
	void AutoPress(int key);

	// Used to clear all keystates
	void ClearKeyBuffer();
}
