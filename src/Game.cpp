#include "Game.h"
#include "Resources.h"

#include <iostream>
#include <string>
#include <ctime>

#define FPS 33

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

Game* Game::getInstance(std::string title, int w, int h)
{
	if (!_instance)
		_instance = new Game(title, w, h);
	return _instance;
}

Game* Game::getInstance(void)
{
	return _instance;
}


SDL_Renderer* Game::getRenderer(void)
{
	return renderer;
}

State& Game::getState(void)
{
	return *state;
}

void Game::run(void)
{
	state = new State();

	int lastTime = SDL_GetTicks();
	while (!state->isQuitRequested())
	{
		int current = SDL_GetTicks();
		int elapsed = current - lastTime;

		state->update(0.0);
		state->render();
		SDL_RenderPresent(renderer);

		if (elapsed < FPS)
			SDL_Delay(FPS - elapsed);
		lastTime = current;
	}

	Resources::clearImages();
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

}

