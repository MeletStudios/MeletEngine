#include "game.h"

const int thickness = 15;
const int paddleH = 100;

Game::Game()
:mWindow(nullptr)
, mRenderer(nullptr)
, mIsRunning(true)
, mTicksCount(0)
{
	
}

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow("Melet Engine", 100, 100, 1024, 768, 0);
	if (!mWindow) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer) {
		SDL_Log("Unable to creater renderer: %s", SDL_GetError());
		return false;
	}
	//
	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768 / 2.0f;

	mPaddle2Pos.x = 768.0f;
	mPaddle2Pos.y = 768 / 2.0f;

	mBallPos.x = 1024 / 2.0f;
	mBallPos.y = 768 / 2.0f;

	mBallVel.x = -200.0f;
	mBallVel.y = 235.0f;

	return true;
}

void Game::ShutDown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}

void Game::ProcessInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
			// End when the event has hit SDL_QUIT
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}

		// End the application simply by pressing escape.
		const Uint8* state = SDL_GetKeyboardState(NULL);
		if (state[SDL_SCANCODE_ESCAPE]) {
			mIsRunning = false;
		}

		mPaddleDir = 0;
		if (state[SDL_SCANCODE_W]) {
			mPaddleDir -= 1;
		}

		if (state[SDL_SCANCODE_S]) {
			mPaddleDir += 1;
		}

		mPaddle2Dir = 0;
		if (state[SDL_SCANCODE_I]) {
			mPaddle2Dir -= 1;
		}

		if (state[SDL_SCANCODE_K]) {
			mPaddle2Dir += 1;
		}
	}
}

void Game::UpdateGame() {
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 8));

	// Delta time is the difference in ticks from last frame (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

	// Update ticks count for next frame
	mTicksCount = SDL_GetTicks();

	// Clamp maximum delta value
	if (deltaTime > 0.05f) {
		deltaTime = 0.05f;
	}

	//TODO: Update Objects in game world as functions of delta time!
	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;

		// Make sure the paddle doesn't move off-screen
		if (mPaddlePos.y < (paddleH / 2.0f + thickness)) {
			mPaddlePos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddlePos.y > (768 - paddleH / 2.0f - thickness)) {
			mPaddlePos.y = 768 - paddleH / 2.0f - thickness;
		}
	}

	// Update second Player
	if (mPaddle2Dir != 0) {
		mPaddle2Pos.y += mPaddle2Dir * 300.0f * deltaTime;

		// Make sure the paddle doesn't move off-screen
		if (mPaddle2Pos.y < (paddleH / 2.0f + thickness)) {
			mPaddle2Pos.y = paddleH / 2.0f + thickness;
		}
		else if (mPaddle2Pos.y > (768 - paddleH / 2.0f - thickness)) {
			mPaddle2Pos.y = 768 - paddleH / 2.0f - thickness;
		}
	}

	// Update the Position of the Ball.
	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	// Did we intersect with the paddle?
	float diff = mPaddlePos.y - mBallPos.y;
	float diff2 = mBallPos.y - mPaddle2Pos.y;

	// Take absolute value of difference
	diff = (diff > 0.0f) ? diff : -diff;
	diff2 = (diff2 > 0.0f) ? diff2 : -diff2;

	if (diff <= paddleH / 2.0f && mBallPos.x <= 25.0f && mBallPos.x >= 20.0f && mBallVel.x < 0.0f) {
		mBallVel.x *= -1.0f;
	}
	else if (diff2 <= paddleH / 2.0f && mBallPos.x >= 768 - 25.0f && mBallPos.x <= 768 - 20.0f && mBallVel.x > 0.0f) {
		mBallVel.x *= -1.0f; // Reverse the ball's horizontal velocity
	}


	// Did the ball go off the screen?
	else if (mBallPos.x <= 0.0f) {
		mIsRunning = false;
	}
	// Did the ball collide with the right wall?
	else if (mBallPos.x >= (1024 - thickness) && mBallVel.x > 0.0f) {
		mBallVel.x *= -1.0f;
	}

	// Did the ball collide with the top wall?
	if (mBallPos.y <= thickness && mBallVel.y < 0.0f) {
		mBallVel.y *= -1;
	}
	// Did the ball collide with the bottom wall?
	else if (mBallPos.y >= (768 - thickness) && mBallVel.y > 0.0f) {
		mBallVel.y *= -1;
	}
}

void Game::GenerateOutput() {
	// Render the colors (R,G,B,A)
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);

	// Clear the back buffers
	SDL_RenderClear(mRenderer);

	// Draw top wall
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);
	SDL_Rect wall{
		0,	// x
		0,	// y
		1024, // width
		thickness // height
	};
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw bottom wall
	wall.y = 768 - thickness;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw the right wall
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024;
	SDL_RenderFillRect(mRenderer, &wall);

	// Draw the paddle
	SDL_Rect paddle1{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2),
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddle1);

	// Draw the second paddle
	SDL_Rect paddle2{
		static_cast<int>(mPaddle2Pos.x),
		static_cast<int>(mPaddle2Pos.y - paddleH / 2),
		thickness,
		paddleH
	};
	SDL_RenderFillRect(mRenderer, &paddle2);

	// Draw the ball
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness / 2),
		static_cast<int>(mBallPos.y - thickness / 2),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);

	// Swap the front and back buffers.
	SDL_RenderPresent(mRenderer);
}