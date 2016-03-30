#include "State.h"
#include "SDL2/SDL.h"

#define UNUSED_VAR (void)

State::State(void)
{
	bg = new Sprite("img/ocean.jpg");
	quitRequested = false;
}

State::~State(void)
{
	delete bg;
}


bool State::isQuitRequested(void)
{
	return quitRequested;
}

void State::update(float dt)
{
	UNUSED_VAR dt;
	if (SDL_QuitRequested())
		quitRequested = true;
}

void State::render(void)
{
	bg->render(0, 0);
}

