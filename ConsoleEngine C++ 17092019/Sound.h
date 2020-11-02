#pragma once
#include "Console.h"

namespace Sound
{
	// Used to play a sound
	void Play(const char* sound);

	// Used to play a beep
	void PlayBeep(int frequency, int duration);

	// Used to stop sound
	void Stop();

	// Used to toggle sound on/off
	void SwitchEnableSound(bool soundState);
}
