#include <math.h>

#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"

#define SPEED 100
#define PRECISION 0.001

Alien::Alien(float x, float y, int nMinions) : sp("img/alien.png"),
											   speed(0.0, 0.0),
											   finalPos(x, y),
											   hp(1000),
											   moving(false)
{
	rotation = 0;
	box.dim.x = sp.getWidth();
	box.dim.y = sp.getHeight();
	box.pos.x = x - box.dim.x/2;
	box.pos.y = y - box.dim.y/2;
	for (int i = 0; i < nMinions; i++)
		minionArray.emplace_back(new Minion(this, i*(2*M_PI/nMinions)));
}

void Alien::update(float dt)
{
	getTaskFromInput();
	handleFirstTaskfromQueue();

	rotation -= 0.25;

	if (moving)
	{
		box.pos += speed*dt;
		if (((box.pos.x > finalPos.x && speed.x >= 0) ||
			(box.pos.x < finalPos.x && speed.x <= 0)) &&
		   	((box.pos.y > finalPos.y && speed.y >= 0) ||
			(box.pos.y < finalPos.y && speed.y <= 0)))
		{
			box.pos = finalPos;
			moving = false;
		}
	}

	for (unsigned int i = 0; i < minionArray.size(); ++i)
		minionArray[i]->update(dt);
}

void Alien::render(void)
{
	sp.render(box.pos.x - box.dim.x/2 - Camera::pos.x,
			box.pos.y - box.dim.y/2 - Camera::pos.y, rotation);
	for (unsigned int i = 0; i < minionArray.size(); ++i)
		minionArray[i]->render();
}

bool Alien::isDead(void)
{
	return (hp > 0) ? false : true;
}

Alien::Action::Action(ActionType type, float x, float y)
{
	this->type = type;
	pos.x = x;
	pos.y = y;
}

/*
 * PRIVATE METHODS
 */
void Alien::getTaskFromInput(void)
{
	InputManager input = InputManager::getInstance();

	if (input.isMouseDown(RIGHT_MOUSE_BUTTON))
		taskQueue.emplace(Action(Action::MOVE,
					input.getMouseX() + Camera::pos.x,
					input.getMouseY() + Camera::pos.y));
	if (input.mousePress(LEFT_MOUSE_BUTTON))
		taskQueue.emplace(Action(Action::SHOOT,
					input.getMouseX() + Camera::pos.x,
					input.getMouseY() + Camera::pos.y));
}

void Alien::handleFirstTaskfromQueue(void)
{
	if (taskQueue.empty())
		return;

	Vec2 mousePos = taskQueue.front().pos;
	if ((taskQueue.front().type == Action::MOVE) &&
			(!((int)box.pos.x == (int)mousePos.x &&
			   (int)box.pos.y == (int)mousePos.y)))
	{
		finalPos = mousePos;
		Vec2 route = box.pos - finalPos;
		route = route/route.getModule();
		speed = route*SPEED;
		moving = true;
	}
	else if (taskQueue.front().type == Action::SHOOT)
	{
		int index = 0;
		float closest = 9999999999999.9;
		for (unsigned int i = 0; i < minionArray.size(); i++)
		{
			float d = (mousePos - minionArray[i]->box.pos).getModule();
			if (d < closest)
			{
				closest = d;
				index = i;
			}
		}
		minionArray[index]->shoot(mousePos);
	}
	taskQueue.pop();
}

