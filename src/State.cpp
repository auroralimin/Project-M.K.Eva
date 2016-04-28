#include <iostream>
#include "State.h"
#include "Face.h"
#include "InputManager.h"

#define UNUSED_VAR (void)

State::State(void) : bg("img/ocean.jpg"),
					 quitRequested(false),
					 objectArray(),
					 tileSet(64, 64, "img/tileset.png"),
					 tileMap("map/tileMap.txt", &tileSet) {}

State::~State(void)
{
	objectArray.clear();
}


bool State::isQuitRequested(void)
{
	return quitRequested;
}

void State::update(float dt)
{
	InputManager input = InputManager::getInstance(); 
	UNUSED_VAR dt;

	quitRequested = (input.isKeyDown(ESCAPE_KEY) || input.isQuitRequested());
	if (input.keyPress(SPACEBAR))
		addObject(input.getMouseX(), input.getMouseY());

	for (unsigned int i = 0; i < objectArray.size(); ++i)
	{
		objectArray[i]->update(0.0);
		if (objectArray[i]->isDead())
			objectArray.erase(objectArray.begin() + i);
	}

	if (SDL_QuitRequested())
		quitRequested = true;
}

void State::render(void)
{
	bg.render(0, 0, 0.0);
	tileMap.render();
	for (unsigned int i = 0; i < objectArray.size(); ++i)
		objectArray[i]->render();
}

/*
 * PRIVATE METHODS
 */
void State::addObject(int mouseX, int mouseY)
{
	Face *face = new Face(mouseX, mouseY, rand() % 360);
	float angle = ((((float)(rand() % 360))*M_PI)/180.0);
	face->box.rotate(200, 0, angle);
	objectArray.emplace_back(face);
}

