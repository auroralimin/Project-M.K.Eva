#include "Camera.h"
#include "InputManager.h"
#include <iostream>

#define BASE_SPEED 0.5

Vec2 Camera::pos = Vec2(0, 0);
Vec2 Camera::speed = Vec2(0, 0);
GameObject* Camera::focus = nullptr;

void Camera::follow(GameObject *newFocus)
{
	focus = newFocus;
}

void Camera::unfollow(void)
{
	focus = nullptr;
}

void Camera::update(float dt, int mapWidth, int mapHeight)
{
	float dSpeed = dt * BASE_SPEED;
	InputManager input = InputManager::getInstance();
	
	if (focus)
		pos = Vec2(focus->box.x, focus->box.y);
	else
	{
		speed = Vec2(0.0, 0.0);
		if ((input.isKeyDown(RIGHT_ARROW_KEY)) &&
				((pos.x + dSpeed) < mapWidth-1024))
			speed = Vec2(dSpeed, 0);
		else if ((input.isKeyDown(LEFT_ARROW_KEY)) &&
				((pos.x + dSpeed) > 0))
			speed = Vec2(-dSpeed, 0);
		else if ((input.isKeyDown(DOWN_ARROW_KEY)) &&
				((pos.y + dSpeed) < mapHeight-600))
			speed = Vec2(0, dSpeed);
		else if ((input.isKeyDown(UP_ARROW_KEY)) &&
				((pos.y + dSpeed) > 0))
			speed = Vec2(0, -dSpeed);
		pos += speed;
	}
}

