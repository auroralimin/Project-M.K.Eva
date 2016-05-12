#include <iostream>
#include "State.h"
#include "InputManager.h"
#include "Camera.h"
#include "Alien.h"
#include "Collision.h"
#include "Penguins.h"
#include "Animation.h"
#include "Game.h"

#define UNUSED_VAR (void)

State::State(void) : bg("img/ocean.jpg"),
					 quitRequested(false),
					 objectArray(),
					 tileSet(64, 64, "img/tileset.png"),
					 tileMap("map/tileMap.txt", &tileSet)
{
	Penguins *penguins = new Penguins(704, 640);
	objectArray.emplace_back(penguins);
	for (int i = 0; i < 5; i++)
		objectArray.emplace_back(new Alien(penguins, 372*i, 237*i, 7));
	Camera::Follow(penguins);
}

State::~State(void)
{
	objectArray.clear();
}


bool State::IsQuitRequested(void)
{
	return quitRequested;
}

void State::Update(float dt)
{
	InputManager input = InputManager::GetInstance(); 
	UNUSED_VAR dt;

	quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());

	for (unsigned int i = 0; i < objectArray.size(); ++i)
	{
		objectArray[i]->Update((float)(dt/1000));
		for (unsigned int j = 0; j < objectArray.size(); ++j)
			if (i != j && objectArray[i]->Is("Bullet") &&
					Collision::IsColliding(objectArray[i]->box, objectArray[j]->box,
						objectArray[i]->rotation, objectArray[j]->rotation))
				objectArray[i]->NotifyCollision(*objectArray[j]);

		if (objectArray[i]->IsDead())
		{
			if (objectArray[i]->Is("Penguins"))
				Camera::Unfollow();
			objectArray.erase(objectArray.begin() + i);
		}
	}
	Camera::Update(dt,
			tileMap.GetWidth()*tileSet.GetTileWidth(),
			tileMap.GetHeight()*tileSet.GetTileWidth());
}

void State::Render(void)
{
	bg.Render(0, 0, 0.0);
	tileMap.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	for (unsigned int i = 0; i < objectArray.size(); ++i)
		objectArray[i]->Render();
	tileMap.RenderLayer(1, Camera::pos.x*1.5, Camera::pos.y*1.5);
}

void State::AddObject(GameObject *ptr)
{
	objectArray.emplace_back(ptr);
}

