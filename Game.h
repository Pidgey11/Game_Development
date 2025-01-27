#pragma once
#include <SDL.h>

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
private:
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	SDL_Window* mWindow;
	bool mIsRunning = true;
	SDL_Renderer* mRenderer;
	Vector2 mPaddlePos;
	Vector2 mBallPos;
};

