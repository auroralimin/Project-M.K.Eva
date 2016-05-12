#include <iostream>
#include "Bullet.h"
#include "Camera.h"
#include "Alien.h"
#include "Penguins.h"

#define UNUSED_VAR (void)
#define PRECISION 0.001

Bullet::Bullet(Vec2 pos, float angle, float speed, float maxDistance,
		std::string sprite, bool targetsPlayer, int frameCount, float frameTime) :
	targetsPlayer(targetsPlayer), sp(sprite, frameCount, frameTime),
	distanceLeft(maxDistance), moving(true)
{
	animationImg = "";
	rotation = angle*(180/M_PI);
	frameCount = 0;
	box.pos = pos;
	box.dim.x = sp.GetWidth();
	box.dim.y = sp.GetHeight();
	this->speed = Vec2(cos(angle), sin(angle))*speed;
	finalPos = Vec2(pos.x + (maxDistance*cos(angle)),
		  		    pos.y + (maxDistance*sin(angle)));
}

void Bullet::Update(float dt)
{
	if (moving)
	{
		distanceLeft -= speed.GetModule()*dt;
		box.pos += speed*dt;
		if (((box.pos.x > finalPos.x && speed.x >= 0) ||
			(box.pos.x < finalPos.x && speed.x <= 0)) &&
		   	((box.pos.y > finalPos.y && speed.y >= 0) ||
			(box.pos.y < finalPos.y && speed.y <= 0)))
			KillBullet();
	}
	sp.Update(dt);
}

void Bullet::Render(void)
{
	sp.Render(box.pos.x - box.dim.x/2 - Camera::pos.x,
			box.pos.y - box.dim.y/2 - Camera::pos.y, rotation);
}

bool Bullet::IsDead(void)
{
	return !moving;
}

void Bullet::NotifyCollision(GameObject &other)
{
	if ((!targetsPlayer && other.Is("Alien")) ||
			(targetsPlayer && other.Is("Penguins")))
	{
		KillBullet();
		other.TakeDamage(1);
	}
}

bool Bullet::Is(std::string className)
{
	return (className == "Bullet");
}

bool Bullet::IsTargetingPlayer(void)
{
	return targetsPlayer;
}

void Bullet::TakeDamage(int dmg)
{
	UNUSED_VAR dmg;
	//DO NOTHING
}

/*
 *	PRIVATE METHODS
 */
void Bullet::KillBullet(void)
{
	box.pos = finalPos;
	distanceLeft = 0.0;
	moving = false;
}

