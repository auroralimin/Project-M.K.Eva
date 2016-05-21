#include "Game.h"
#include "StageState.h"
#include "Resources.h"
#include "InputManager.h"

#include <iostream>
#include <string>
#include <ctime>

#define FPS 60
#define FRAME_TIME 1000/FPS

Game* Game::_instance = nullptr;

/*
 * PUBLIC METHODS
 */
Game::~Game(void)
{
	if (storedState != nullptr)
		delete storedState;
	while (!stateStack.empty())
		stateStack.pop();
	srand(time(nullptr));
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	IMG_Quit();
}

Game* Game::GetInstance(std::string title, int w, int h)
{
	if (!_instance)
		_instance = new Game(title, w, h);
	return _instance;
}

Game* Game::GetInstance(void)
{
	return _instance;
}


SDL_Renderer* Game::GetRenderer(void)
{
	return renderer;
}

State& Game::GetCurrentState(void)
{
	return *stateStack.top();
}

void Game::Push(State *state)
{
	storedState = state;
}

void Game::Run(void)
{
	if (storedState == nullptr)
	{
		Resources::ClearImages();
		return;
	}
		
	stateStack.emplace(storedState);
	storedState = nullptr;

	frameStart = SDL_GetTicks();
	while (!stateStack.empty() && !stateStack.top()->IsQuitRequested())
	{
		currentTime = SDL_GetTicks();
		CalculateDeltaTime();

		InputManager::GetInstance().Update();
		stateStack.top()->Update(dt);
		stateStack.top()->Render();
		SDL_RenderPresent(renderer);

		if (stateStack.top()->IsPopRequested())
			stateStack.pop();

		if (storedState != nullptr)
		{
			stateStack.emplace(storedState);
			storedState = nullptr;
		}

		if (dt < FRAME_TIME)
			SDL_Delay(FRAME_TIME - dt);
		frameStart = currentTime;
	}
	Resources::ClearImages();
}

int Game::GetWinWidth(void)
{
	return winWidth;
}

int Game::GetWinHeight(void)
{
	return winHeight;
}

/*
 * PRIVATE METHODS
 */
Game::Game(std::string title, int w, int h)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0)
	{
		std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;
		exit(EXIT_SUCCESS);
	}

	int loaders = IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	if (loaders == 0)
	{
		std::cerr << "Unable to init SDL_Image: " << SDL_GetError() << std::endl;
		exit(EXIT_SUCCESS);
	}

	window = SDL_CreateWindow(title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, 0);
	if (!window)
	{
		std::cerr << "Failed to create a window: " << SDL_GetError() << std::endl;
		exit(EXIT_SUCCESS);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cerr << "Failed to create a renderer: " << SDL_GetError() << std::endl;
		exit(EXIT_SUCCESS);
	}
	winWidth = w, winHeight = h;
	storedState = nullptr;
}

void Game::CalculateDeltaTime(void)
{
	dt = currentTime - frameStart;
}

