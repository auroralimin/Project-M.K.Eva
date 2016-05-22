#include "Alien.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Animation.h"

#define UNUSED_VAR (void)
#define SPEED 100
#define PRECISION 0.001

auto Alien::alienCount = 0;

Alien::Alien(GameObject *focus, float x, float y, int nMinions) :
	focus(focus), sp("img/alien.png"), sound("audio/boom.wav"), speed(0.0, 0.0),
	destination(x, y)
{
	alienCount++;
	animationImg = "img/aliendeath.png";
	frameCount = 4;
	hp = 10;
	rotation = 0;
	box.dim.x = sp.GetWidth();
	box.dim.y = sp.GetHeight();
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

void Alien::Update(float dt)
{
	const float cooldown = 10.0;
	rotation -= 0.25;

	if (state == AlienState::RESTING)
	{
		restTimer.Update(dt);
		destination = focus->box.pos;
		Shoot(dt);
	}

	if (restTimer.Get() > cooldown)
	{
		state = AlienState::MOVING;
		destination = focus->box.pos;
		Vec2 route = box.pos - destination;
		route = route/route.GetModule();
		speed = route*SPEED;
		restTimer.Restart();
	}

	if (state == AlienState::MOVING)
		Move(dt);

	for (unsigned int i = 0; i < minionArray.size(); ++i)
		minionArray[i]->Update(dt);
}

void Alien::Render(void)
{
	sp.Render(box.pos.x - box.dim.x/2 - Camera::pos.x,
			box.pos.y - box.dim.y/2 - Camera::pos.y, rotation);
	for (unsigned int i = 0; i < minionArray.size(); ++i)
		minionArray[i]->Render();
}

bool Alien::IsDead(void)
{
	if (hp > 0)
		return false;

	Game::GetInstance()->GetCurrentState().AddObject(
			new Animation(box.pos, rotation, animationImg, frameCount));
	sound.Play(0);
	for (unsigned int i = 0; i < minionArray.size(); ++i)
		Game::GetInstance()->GetCurrentState().AddObject(
				new Animation(minionArray[i]->box.pos, minionArray[i]->rotation,
					minionArray[i]->animationImg, minionArray[i]->frameCount));
	return true;
}

void Alien::NotifyCollision(GameObject &other)
{
	UNUSED_VAR other;
}

bool Alien::Is(std::string className)
{
	return (className == "Alien");
}

void Alien::TakeDamage(int dmg)
{
	hp = hp - dmg;
}

/*
 * PRIVATE METHODS
 */
void Alien::Shoot(float dt)
{
	static Timer timer = Timer();
	const float shootCooldown = 1;
	static float oldTime = 0.0;
	
	timer.Update(dt);
	if (timer.Get() - oldTime >= shootCooldown)
	{
		oldTime = timer.Get();
		int index = 0;
		float closest = 9999999999999.9;
		for (unsigned int i = 0; i < minionArray.size(); i++)
		{
			float d = (destination - minionArray[i]->box.pos).GetModule();
			if (d < closest)
			{
				closest = d;
				index = i;
			}
		}
		minionArray[index]->Shoot(destination);
	}
}

void Alien::Move(float dt)
{
	box.pos += speed*dt;
	if (((box.pos.x > destination.x && speed.x >= 0) ||
				(box.pos.x < destination.x && speed.x <= 0)) &&
			((box.pos.y > destination.y && speed.y >= 0) ||
			 (box.pos.y < destination.y && speed.y <= 0)))
	{
		box.pos = destination;
		state = AlienState::RESTING;
		restTimer.Restart();
	}
}

