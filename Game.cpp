#include "Game.h"

Game::Game(){}

bool Game::Initialize() {
	int sdlResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlResult != 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}

	mWindow = SDL_CreateWindow(
		"Game programming in C++",
		100, // x-cordinate
		100, // y-cordinate
		1024, // Width
		768, // height
		0 // Flags
	);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
}

void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void Game::UpdateGame()
{
}
void Game::ProcessInput() {
}

void Game::GenerateOutput() {
}
void Game::RunLoop() {
	while (mIsRunning){
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}