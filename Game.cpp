#include "Game.h"
const int thickness = 15;
const float paddleH = 100.0f;
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

	mPaddlePos.x = 10.0f;
	mPaddlePos.y = 768.0f / 2.0f;
	mBallPos.x = 1024.0f / 2.0f;
	mBallPos.y = 768.0f / 2.0f;
	mBallVel.x = -100.0f;
	mBallVel.y = -120.0f;
}

void Game::Shutdown() {
	SDL_DestroyWindow(mWindow);
	SDL_DestroyRenderer(mRenderer);
	SDL_Quit();
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
	

	if (mPaddleDir != 0) {
		mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
		
		// Make sure paddle doesnt move off the screen
		if (mPaddlePos.y < (paddleH / 2.0f + thickness))
			mPaddlePos.y = paddleH / 2.0f + thickness;
		else if (mPaddlePos.y > (768.0f - paddleH / 2.0f - thickness))
			mPaddlePos.y = 768.0f - paddleH / 2.0f - thickness;
	}

	mBallPos.x += mBallVel.x * deltaTime;
	mBallPos.y += mBallVel.y * deltaTime;

	if (mBallPos.y <= thickness && mBallVel.y < 0.0f) // Colision with top wall
		mBallVel.y *= -1;
	if(mBallPos.y >= (768.0f - thickness) && mBallVel.y > 0.0f) // Colision with bottom wall
		mBallVel.y *= -1;

	float diff = mPaddlePos.y - mBallPos.y;
	diff = (diff > 0.0f) ? diff : -diff;
	if (
		// Our y-difference is small enough
		diff <= paddleH / 2.0f &&
		// Ball is at the correct x position
		mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
		//The ball is moving to the left
		mBallVel.x < 0.0f
		)
		mBallVel.x *= -1.0f;
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
	
	mPaddleDir = 0;
	if (state[SDL_SCANCODE_W])
		mPaddleDir -= 1; 
	if (state[SDL_SCANCODE_S])
		mPaddleDir += 1;
}

void Game::GenerateOutput() {
	SDL_SetRenderDrawColor(
		mRenderer,
		0,		//R
		0,		//G
		255,	//B
		255		//A
	);
	SDL_RenderClear(mRenderer);
	SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255); // Draw walls

	SDL_Rect wall{
		0,	//x
		0,	//y
		1024,	//width
		thickness	//height
	};
	SDL_RenderFillRect(mRenderer, &wall);
	
	wall.y = 768 - thickness; // bottom wall
	
	SDL_RenderFillRect(mRenderer, &wall);
	
	wall.x = 1024 - thickness;
	wall.y = 0;
	wall.w = thickness;
	wall.h = 1024; // Right wall
	SDL_RenderFillRect(mRenderer, &wall);

	SDL_Rect paddle{
		static_cast<int>(mPaddlePos.x),
		static_cast<int>(mPaddlePos.y - paddleH / 2 ),
		thickness,
		static_cast<int>(paddleH)
	};
	SDL_RenderFillRect(mRenderer, &paddle);
	
	SDL_Rect ball{
		static_cast<int>(mBallPos.x - thickness /2 ),
		static_cast<int>(mBallPos.y - thickness /2 ),
		thickness,
		thickness
	};
	SDL_RenderFillRect(mRenderer, &ball);
	SDL_RenderPresent(mRenderer);
}
void Game::RunLoop() {
	while (mIsRunning){
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
}