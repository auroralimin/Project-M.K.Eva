#include <iostream>
#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "Alien.h"
#include "Collision.h"
#include "Penguins.h"

#define UNUSED_VAR (void)

State::State(void) : bg("img/ocean.jpg"),
					 quitRequested(false),
					 objectArray(),
					 tileSet(64, 64, "img/tileset.png"),
					 tileMap("map/tileMap.txt", &tileSet)
{
	objectArray.emplace_back(new Alien(512, 300, 7));
	Penguins *penguins = new Penguins(704, 640);
	objectArray.emplace_back(penguins);
	Camera::follow(penguins);
}

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

	for (unsigned int i = 0; i < objectArray.size(); ++i)
	{
		objectArray[i]->update((float)(dt/1000));
		for (unsigned int j = 0; j < objectArray.size(); ++j)
			if (i != j && objectArray[i]->is("Bullet") &&
					Collision::isColliding(objectArray[i]->box, objectArray[j]->box,
						objectArray[i]->rotation, objectArray[j]->rotation))
				objectArray[i]->notifyCollision(*objectArray[j]);

		if (objectArray[i]->isDead())
		{
			if (objectArray[i]->is("Penguins"))
				Camera::unfollow();
			objectArray.erase(objectArray.begin() + i);
		}
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

void State::addObject(GameObject *ptr)
{
	objectArray.emplace_back(ptr);
}

