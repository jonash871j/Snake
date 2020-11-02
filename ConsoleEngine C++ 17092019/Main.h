#pragma once
#include <chrono>

class Main
{
private:
	bool terminateConsole = false;

public:
	void Start();
	void Update();

public:
	READONLY_PROPERTY(int, TerminateConsole);
	GET(TerminateConsole) { return terminateConsole; }
};

#pragma region
#define start Main::Start
#define update Main::Update
int main() 
{ 
	Main game; 
	game.Start(); 
	while (!game.TerminateConsole) {
		game.Update();
	}
	return 0; 
}

#pragma endregion