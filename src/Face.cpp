#include <iostream>
#include "Face.h"
#include "InputManager.h"
#include "Camera.h"

#define UNUSED_VAR (void)

Face::Face(int x, int y, float angle) : sp("img/penguinface.png")
{
	box.dim.x = sp.getWidth();
	box.dim.y = sp.getHeight();
	box.pos.x = x - (int)(box.dim.x/2);
	box.pos.y = y - (int)(box.dim.y/2);
	hitPoints = 1;
	this->angle = angle;
}

void Face::damage(int damage)
{
	hitPoints -= damage;
}

void Face::update(float dt)
{
	UNUSED_VAR dt;
	InputManager input = InputManager::getInstance();

	if (input.isMouseDown(LEFT_MOUSE_BUTTON) &&
			box.isInside(Vec2(input.getMouseX() + Camera::pos.x,
					   	 	  input.getMouseY() + Camera::pos.y)))
    	damage(rand() % 10 + 10);
}

void Face::render(void)
{
	sp.render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y, angle);
}

bool Face::isDead(void)
{
	return (hitPoints > 0) ? false : true;
}

