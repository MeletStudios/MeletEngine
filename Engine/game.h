#pragma once
#include <SDL.h>

struct Vector2 {
	float x;
	float y;
};

class Game {
public:
	Game();

	bool Initialize();

	void RunLoop();
	void ShutDown();

private:
	void ProcessInput();
	//void UpdateGame();
	void GenerateOutput();

	SDL_Window* mWindow;
	bool mIsRunning;

	SDL_Renderer* mRenderer;

	// Position of paddle
	Vector2 mPaddlePos;

	// Position of Ball
	Vector2 mBallPos;
};

