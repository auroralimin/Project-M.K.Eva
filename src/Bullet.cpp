#include "Bullet.h"

Bullet::Bullet(Vec2 pos, float angle, float speed, float maxDistance, 
			std::string sprite, int frameCount, float frameTime, 
			bool targetsPlayer)
{
	sp = Sprite(sprite, frameCount, frameTime);
	this->targetsPlayer = targetsPlayer;
	box.pos = pos;
	box.dim.x = sp.GetWidth();
	box.dim.y = sp.GetHeight();
	distanceLeft = maxDistance;

	this->speed.x = speed*cos(angle);
	this->speed.y = speed*sin(angle);
	rotation = angle;
}

void Bullet::Update(float dt)
{
	box.pos += speed*dt;
	sp.Update(dt);
	distanceLeft -= speed.Mag()*dt;
}

void Bullet::Render()
{
	sp.Render(box.pos.x, box.pos.y, rotation*180/M_PI);
}

bool Bullet::IsDead()
{
	return (distanceLeft <= 0);
}

void Bullet::NotifyCollision(GameObject &other)
{

}

bool Bullet::Is(std::string className)
{
	return ("Bullet" == className);
}

void Bullet::TakeDamage(int dmg) {}
