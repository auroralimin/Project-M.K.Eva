#include <iostream>

#include "StageState.h"
#include "TitleState.h"
#include "InputManager.h"
#include "Camera.h"
#include "Alien.h"
#include "Collision.h"
#include "Penguins.h"
#include "Animation.h"
#include "Game.h"

#define UNUSED_VAR (void)

StageState::StageState(void) : bg("img/ocean.jpg"),
					 music("audio/stageState.ogg"),
					 tileSet(64, 64, "img/tileset.png"),
					 tileMap("map/tileMap.txt", &tileSet)
{
	Penguins *penguins = new Penguins(704, 640);
	objectArray.emplace_back(penguins);
	for (int i = 0; i < 5; i++)
		objectArray.emplace_back(new Alien(penguins, 372*i, 237*i, 7));
	Camera::Follow(penguins);
	music.Play(-1);
}

StageState::~StageState(void)
{
	objectArray.clear();
}

void StageState::Update(float dt)
{
	InputManager input = InputManager::GetInstance(); 
	UNUSED_VAR dt;

	if (input.KeyPress(ESCAPE_KEY))
	{
		Pause();
		Game::GetInstance()->Push(new TitleState());
	}

	quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());
	UpdateArray(dt);

	Camera::Update(dt,
			tileMap.GetWidth()*tileSet.GetTileWidth(),
			tileMap.GetHeight()*tileSet.GetTileWidth());
}

void StageState::Render(void)
{
	bg.Render(0, 0, 0.0);
	tileMap.RenderLayer(0, Camera::pos.x, Camera::pos.y);
	for (unsigned int i = 0; i < objectArray.size(); ++i)
		objectArray[i]->Render();
	tileMap.RenderLayer(1, Camera::pos.x*1.5, Camera::pos.y*1.5);
}

void StageState::Pause(void)
{
	music.Stop();
}

void StageState::Resume(void)
{
	music.Play(-1);
}

/*
 * Protected Methods
 */
void StageState::UpdateArray(float dt)
{
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
}

