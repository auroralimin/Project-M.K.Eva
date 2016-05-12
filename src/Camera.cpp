#include "Camera.h"
#include "Game.h"
#include "InputManager.h"
#include <iostream>

#define BASE_SPEED 0.5

Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject *newFocus)
{
	focus = newFocus;
}

void Camera::Unfollow(void)
{
	focus = nullptr;
}

void Camera::Update(float dt, int mapWidth, int mapHeight)
{
	float dSpeed = dt * BASE_SPEED;
	InputManager input = InputManager::GetInstance();
	
	if (focus)
		pos = Vec2(focus->box.pos.x-Game::GetInstance()->GetWinWidth()/2,
				focus->box.pos.y-Game::GetInstance()->GetWinHeight()/2);
	else
	{
		speed = Vec2(0.0, 0.0);
		if ((input.IsKeyDown(RIGHT_ARROW_KEY)) &&
				((pos.x + dSpeed) < mapWidth-1024))
			speed = Vec2(dSpeed, 0);
		else if ((input.IsKeyDown(LEFT_ARROW_KEY)) &&
				((pos.x + dSpeed) > 0))
			speed = Vec2(-dSpeed, 0);
		else if ((input.IsKeyDown(DOWN_ARROW_KEY)) &&
				((pos.y + dSpeed) < mapHeight-600))
			speed = Vec2(0, dSpeed);
		else if ((input.IsKeyDown(UP_ARROW_KEY)) &&
				((pos.y + dSpeed) > 0))
			speed = Vec2(0, -dSpeed);
		pos += speed;
	}
}

