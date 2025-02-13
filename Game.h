#pragma once
#include <SDL.h>
#include <vector>

struct Vector2
{
	float x;
	float y;
};

class Game
{
public:
	Game();
	//Initialize the game
	bool Initialize();
	void RunLoop();
	void Shutdown();
	void AddActor(class Actor* actor);
	void RemoveActor(class Actor* actor);
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	SDL_Window* mWindow;
	bool mIsRunning = true;
	SDL_Renderer* mRenderer;
	Uint32 mTicksCount;		//Number of ticks since game start
	// All the actors in the game
	std::vector<class Actor*> mActors;
	// Any pending actors
	std::vector<class Actor*> mPendingActors;
	bool mUpdatingActors;
	bool GameFinished = false;
};

