#include "State.h"
#include "Face.h"
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
	objectArray.clear();
}


bool State::isQuitRequested(void)
{
	return quitRequested;
}

void State::update(float dt)
{
	UNUSED_VAR dt;

	input();
	for (unsigned int i = 0; i < objectArray.size(); ++i)
		if (objectArray[i]->isDead())
			objectArray.erase(objectArray.begin() + i);

	if (SDL_QuitRequested())
		quitRequested = true;
}

void State::render(void)
{
	bg->render(0, 0, 0.0);
	for (unsigned int i = 0; i < objectArray.size(); ++i)
		((Face*)objectArray[i])->render();
}

void State::input(void)
{
    SDL_Event event;
    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    while (SDL_PollEvent(&event))
	{
        if (event.type == SDL_QUIT)
            quitRequested = true;
        
        if (event.type == SDL_MOUSEBUTTONDOWN)
		{
            for (int i = objectArray.size() - 1; i >= 0; --i)
			{
                Face* face = (Face*) objectArray[i];
                if (face->box.isInside(mouseX, mouseY))
				{
                    face->damage(rand() % 10 + 10);
                    break;
                }
            }
        }

        if (event.type == SDL_KEYDOWN)
		{
            if (event.key.keysym.sym == SDLK_ESCAPE)
                quitRequested = true;
            else
                addObject(mouseX, mouseY);
        }
    }
}

void State::addObject(int mouseX, int mouseY)
{
	objectArray.emplace_back(new Face(mouseX, mouseY, rand() % 360));		
}

