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
	rotation = angle*(180/M_PI);
	box.pos = pos;
	box.dim.x = sp.getWidth();
	box.dim.y = sp.getHeight();
	this->speed = Vec2(cos(angle), sin(angle))*speed;
	finalPos = Vec2(pos.x + (maxDistance*cos(angle)),
		  		    pos.y + (maxDistance*sin(angle)));
}

void Bullet::update(float dt)
{
	if (moving)
	{
		distanceLeft -= speed.getModule()*dt;
		box.pos += speed*dt;
		if (((box.pos.x > finalPos.x && speed.x >= 0) ||
			(box.pos.x < finalPos.x && speed.x <= 0)) &&
		   	((box.pos.y > finalPos.y && speed.y >= 0) ||
			(box.pos.y < finalPos.y && speed.y <= 0)))
			killBullet();
	}
	sp.update(dt);
}

void Bullet::render(void)
{
	sp.render(box.pos.x - box.dim.x/2 - Camera::pos.x,
			box.pos.y - box.dim.y/2 - Camera::pos.y, rotation);
}

bool Bullet::isDead(void)
{
	return !moving;
}

void Bullet::notifyCollision(GameObject &other)
{
	if ((!targetsPlayer && other.is("Alien")) ||
			(targetsPlayer && other.is("Penguins")))
	{
		killBullet();
		other.takeDamage(1);
	}
}

bool Bullet::is(std::string className)
{
	return (className == "Bullet");
}

bool Bullet::isTargetingPlayer(void)
{
	return targetsPlayer;
}

void Bullet::takeDamage(int dmg)
{
	UNUSED_VAR dmg;
	//DO NOTHING
}

/*
 *	PRIVATE METHODS
 */
void Bullet::killBullet(void)
{
	box.pos = finalPos;
	distanceLeft = 0.0;
	moving = false;
}

