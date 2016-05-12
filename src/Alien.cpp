#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Animation.h"

#define UNUSED_VAR (void)
#define SPEED 100
#define PRECISION 0.001

Alien::Alien(float x, float y, int nMinions) : sp("img/alien.png"),
											   speed(0.0, 0.0),
											   finalPos(x, y),
											   moving(false)
{
	animationImg = "img/aliendeath.png";
	frameCount = 4;
	hp = 10;
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
	//getTaskFromInput();
	//handleFirstTaskfromQueue();

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
	if (hp > 0)
		return false;

	Game::getInstance()->getState().addObject(
			new Animation(box.pos, rotation, animationImg, frameCount));
	for (unsigned int i = 0; i < minionArray.size(); ++i)
		Game::getInstance()->getState().addObject(
				new Animation(minionArray[i]->box.pos, minionArray[i]->rotation,
					minionArray[i]->animationImg, minionArray[i]->frameCount));
	return true;
}

void Alien::notifyCollision(GameObject &other)
{
	UNUSED_VAR other;
}

bool Alien::is(std::string className)
{
	return (className == "Alien");
}

void Alien::takeDamage(int dmg)
{
	hp = hp - dmg;
}

/*
 * PRIVATE METHODS
 */

Alien::Action::Action(ActionType type, float x, float y)
{
	this->type = type;
	pos.x = x;
	pos.y = y;
}

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
		//minionArray[index]->shoot(mousePos);
	}
	taskQueue.pop();
}

