#include <iostream>
#include "State.h"
#include "Face.h"
#include "InputManager.h"
#include "Camera.h"

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
		addObject(input.getMouseX() + Camera::pos.x,
				  input.getMouseY() + Camera::pos.y);

	for (unsigned int i = 0; i < objectArray.size(); ++i)
	{
		objectArray[i]->update((float)(dt/1000));
		if (objectArray[i]->isDead())
			objectArray.erase(objectArray.begin() + i);
	}
	Camera::update(dt,
				   tileMap.getWidth()*tileSet.getTileWidth(),
				   tileMap.getHeight()*tileSet.getTileWidth());
}

void State::render(void)
{
	bg.render(0, 0, 0.0);
	tileMap.renderLayer(0, Camera::pos.x, Camera::pos.y);
	for (unsigned int i = 0; i < objectArray.size(); ++i)
		objectArray[i]->render();
	tileMap.renderLayer(1, Camera::pos.x*1.5, Camera::pos.y*1.5);
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

