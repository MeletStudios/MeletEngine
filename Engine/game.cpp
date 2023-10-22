#include "game.h"

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

	return true;
}

void Game::ShutDown() {
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::RunLoop() {
	while (mIsRunning) {
		ProcessInput();
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
	}
}