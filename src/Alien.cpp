#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Animation.h"

#define UNUSED_VAR (void)
#define SPEED 100
#define PRECISION 0.001

int Alien::alienCount = 0;

Alien::Alien(GameObject *focus, float x, float y, int nMinions) :
	focus(focus), sp("img/alien.png"), speed(0.0, 0.0), destination(x, y)
{
	alienCount++;
	animationImg = "img/aliendeath.png";
	frameCount = 4;
	hp = 10;
	rotation = 0;
	box.dim.x = sp.getWidth();
	box.dim.y = sp.getHeight();
	box.pos.x = x - box.dim.x/2;
	box.pos.y = y - box.dim.y/2;
	state = AlienState::RESTING;
	restTimer = Timer();
	for (int i = 0; i < nMinions; i++)
		minionArray.emplace_back(new Minion(this, i*(2*M_PI/nMinions)));
}

Alien::~Alien(void)
{
	alienCount--;
}

void Alien::update(float dt)
{
	const float cooldown = 10.0;
	rotation -= 0.25;

	if (state == AlienState::RESTING)
	{
		restTimer.update(dt);
		destination = focus->box.pos;
		shoot(dt);
	}

	if (restTimer.get() > cooldown)
	{
		state = AlienState::MOVING;
		destination = focus->box.pos;
		Vec2 route = box.pos - destination;
		route = route/route.getModule();
		speed = route*SPEED;
		restTimer.restart();
	}

	if (state == AlienState::MOVING)
		move(dt);

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
void Alien::shoot(float dt)
{
	static Timer timer = Timer();
	const float shootCooldown = 1;
	static float oldTime = 0.0;
	
	timer.update(dt);
	if (timer.get() - oldTime >= shootCooldown)
	{
		oldTime = timer.get();
		int index = 0;
		float closest = 9999999999999.9;
		for (unsigned int i = 0; i < minionArray.size(); i++)
		{
			float d = (destination - minionArray[i]->box.pos).getModule();
			if (d < closest)
			{
				closest = d;
				index = i;
			}
		}
		minionArray[index]->shoot(destination);
	}
}

void Alien::move(float dt)
{
	box.pos += speed*dt;
	if (((box.pos.x > destination.x && speed.x >= 0) ||
				(box.pos.x < destination.x && speed.x <= 0)) &&
			((box.pos.y > destination.y && speed.y >= 0) ||
			 (box.pos.y < destination.y && speed.y <= 0)))
	{
		box.pos = destination;
		state = AlienState::RESTING;
		restTimer.restart();
	}
}

