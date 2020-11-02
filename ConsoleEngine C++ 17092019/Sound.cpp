#include "Sound.h"
#include <Windows.h>

bool enableSound = true;

//Used to play a sound
void Sound::Play(const char* sound)
{
	if (enableSound == true)
		PlaySound(sound, NULL, SND_ASYNC);
}

// Used to play a beep
void Sound::PlayBeep(int frequency, int duration)
{
	if (enableSound == true)
		Beep(frequency, duration);
}

// Used to stop a sound
void Sound::Stop()
{
	PlaySound(NULL, NULL, SND_ASYNC);
}

// Used to toggle sound on/off
void Sound::SwitchEnableSound(bool soundState)
{
	enableSound = soundState;
}