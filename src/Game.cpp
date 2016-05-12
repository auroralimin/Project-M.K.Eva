#include "Game.h"
#include "Resources.h"
#include "InputManager.h"

#include <iostream>
#include <string>
#include <ctime>

#define FPS 40

Game* Game::_instance = nullptr;

/*
 * PUBLIC METHODS
 */
Game::~Game(void)
{
	srand(time(NULL));
	delete state;
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

State& Game::GetState(void)
{
	return *state;
}

void Game::Run(void)
{
	state = new State();

	frameStart = SDL_GetTicks();
	while (!state->IsQuitRequested())
	{
		currentTime = SDL_GetTicks();
		CalculateDeltaTime();

		InputManager::GetInstance().Update();
		state->Update(dt);
		state->Render();
		SDL_RenderPresent(renderer);

		if (dt < FPS)
			SDL_Delay(FPS - dt);
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
}

void Game::CalculateDeltaTime(void)
{
	dt = currentTime - frameStart;
}

