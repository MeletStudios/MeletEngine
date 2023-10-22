#pragma once
#include <SDL.h>

class Game {
public:
	// Game();

	bool Initialize();

	void RunLoop();
	void ShutDown();

private:
	void ProcessInput();
	/*void UpdateGame();
	void GenerateOutput();*/

	SDL_Window* mWindow;
	bool mIsRunning;
};

