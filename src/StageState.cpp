#include <iostream>

#include "StageState.h"
#include "TitleState.h"
#include "EndState.h"
#include "InputManager.h"
#include "Camera.h"
#include "Alien.h"
#include "Collision.h"
#include "Penguins.h"
#include "Animation.h"
#include "Game.h"
#include "Timer.h"

#define UNUSED_VAR (void)

StageState::StageState(void) : bg("img/ocean.jpg"),
					 music("audio/stageState.ogg"),
					 tileSet(64, 64, "img/tileset.png"),
					 tileMap("map/tileMap.txt", &tileSet),
					 data(),
					 endGame(false)
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
	static Timer timer = Timer();
	InputManager input = InputManager::GetInstance(); 
	UNUSED_VAR dt;

	if (endGame)
		timer.Update(dt);

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

	if (timer.Get() >= 1000)
	{
		Game::GetInstance()->GetCurrentState().Pause();
		Game::GetInstance()->Push(new EndState(data));
		popRequested = true;
		endGame = false;
		timer.Restart();
	}
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
	bool hasAlien = false;
	for (unsigned int i = 0; i < objectArray.size(); ++i)
	{
		objectArray[i]->Update((float)(dt/1000));
		for (unsigned int j = 0; j < objectArray.size(); ++j)
			if (i != j && objectArray[i]->Is("Bullet") &&
					Collision::IsColliding(objectArray[i]->box, objectArray[j]->box,
						objectArray[i]->rotation, objectArray[j]->rotation))
				objectArray[i]->NotifyCollision(*objectArray[j]);

		if (objectArray[i]->Is("Alien"))
			hasAlien = true;
		if (objectArray[i]->IsDead())
		{
			if (objectArray[i]->Is("Penguins"))
			{
				Camera::Unfollow();
				endGame = true;
				data.playerVictory = false;
			}
			objectArray.erase(objectArray.begin() + i);
		}
	}

	if (!hasAlien)
	{
		endGame = true;
		data.playerVictory = true;
	}
}

