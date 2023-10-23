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
	void UpdateGame();
	void GenerateOutput();

	// Window
	SDL_Window* mWindow;
	bool mIsRunning;

	// Renderer of objects
	SDL_Renderer* mRenderer;

	// Position of paddle
	Vector2 mPaddlePos;
	Vector2 mPaddle2Pos;

	// Position of Ball
	Vector2 mBallPos;

	// Ball Velocity
	Vector2 mBallVel;

	// Ticks per frame
	Uint32 mTicksCount;

	// Paddle direction
	int mPaddleDir;
	int mPaddle2Dir;
};