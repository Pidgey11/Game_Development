#include "Game.h"
#include <algorithm>
#include "Actor.h"
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
	
	mRenderer = SDL_CreateRenderer (
		mWindow, //Window to create renderer for
		-1, // Standard value
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}

}

void Game::Shutdown() {

	while (!mActors.empty()) {
		delete mActors.back();
	}
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
}

void Game::AddActor(Actor* actor) {
	if (mUpdatingActors) {
		mPendingActors.emplace_back(actor);
	}
	else {
		mActors.emplace_back(actor);
	}
}
void Game::UpdateGame()
{
	// Wait until 16ms has elapsed since last frame
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
		;
	
	// Delta time is the difference in ticks from last frame
	// (converted to seconds)
	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
	
	if (deltaTime > 0.05f)
		deltaTime = 0.05f;
	
	// Update ticks count for next frame
	mTicksCount = SDL_GetTicks();
	
	//Update all actors
	mUpdatingActors = true;
	for (auto actor : mActors) {
		actor->Update(deltaTime);
	}
	mUpdatingActors = false;

	//move any pending actors to mActors

	for (auto pending : mPendingActors) {
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	//Add any dead actors to a temp vector

	std::vector<Actor*> deadActors;

	for (auto actor : mActors) {
		if (actor->GetState() == Actor::EDead) {
			deadActors.emplace_back(actor);
		}
	}

	//Delete dead actors
	for (auto actor : deadActors) {
		delete actor;
	}

}
void Game::ProcessInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type)
			case SDL_QUIT:
				mIsRunning = false;
				break;
	}
	const Uint8* state = SDL_GetKeyboardState(NULL);
	if (state[SDL_SCANCODE_ESCAPE]) {
		mIsRunning = false;
	}
	
}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		//R
		0,		//G
		255,	//B
		255		//A
	);
	
}
void Game::RunLoop() {
	while (mIsRunning){
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}