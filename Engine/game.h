#include <SDL.h>
#include <iostream>
#include <vector>

class Game {
public:
	Game();

	bool Initialize();
	void RunLoop();
	void ShutDown();

	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);

private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pendin actors
	std::vector<class Actor*> mPendingActors;

	// SDL Window
	SDL_Window* mWindow;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;
	bool mIsRunning;

	// Track if we're updating the actors
	bool mUpdatingActors;
};

