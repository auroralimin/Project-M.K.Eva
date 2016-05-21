#include <iostream>
#include "Minion.h"
#include "Camera.h"
#include "Game.h"

#define UNUSED_VAR (void)
#define D_RADIUS 100
#define SPEED M_PI/7

Minion::Minion(GameObject *minionCenter, float arcOffSet) :
	center(minionCenter),
	sp("img/minion.png"),
	arc(arcOffSet)
{
	animationImg = "img/miniondeath.png";
	frameCount = 4;
	hp = 0;
	box.dim.x = sp.GetWidth();
	box.dim.y = sp.GetHeight();
	Update(0.0);
	float scale = 1.0 + (rand() % 5)/10.0;
	sp.SetScaleX(scale);
	sp.SetScaleY(scale);
}

void Minion::Update(float dt)
{
	arc += dt*SPEED;
	rotation = arc*(180/M_PI);
	box.pos.x = D_RADIUS*cos(arc) + center->box.pos.x;
	box.pos.y = D_RADIUS*sin(arc) + center->box.pos.y;
}

void Minion::Render(void)
{
	sp.Render(box.pos.x - Camera::pos.x - box.dim.x/2,
			box.pos.y - Camera::pos.y - box.dim.y/2, rotation);
}

bool Minion::IsDead(void)
{
	return false;
}

void Minion::Shoot(Vec2 pos)
{
	float angle = atan2(pos.y - box.pos.y, pos.x - box.pos.x);
	Game::GetInstance()->GetCurrentState().AddObject(new Bullet(box.pos,
				angle, 200, 200, "img/minionbullet2.png", true));
}

void Minion::NotifyCollision(GameObject &other)
{
	UNUSED_VAR other;
}

bool Minion::Is(std::string className)
{
	return (className == "Minion");
}

void Minion::TakeDamage(int dmg)
{
	UNUSED_VAR dmg;
	//D0 NOTHING
}

