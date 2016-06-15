#include "Bullet.h"
#include "Game.h"
#include "Config.h"

Bullet::Bullet(Vec2 pos, float angle, float speed, float maxDistance, 
			std::string sprite, int frameCount, float frameTime, 
			bool targetsPlayer)
{
	sp = Sprite(sprite, frameCount, frameTime);
	this->targetsPlayer = targetsPlayer;
	box.pos = pos;
	box.dim.x = sp.GetWidth();
	box.dim.y = sp.GetHeight();
	hitbox.dim = Vec2(box.dim.x/1.5, box.dim.y/2.5);
	hitbox.pos = Vec2(box.pos.x + 5, box.pos.y + 35); 
	distanceLeft = maxDistance;

	this->speed.x = speed*cos(angle);
	this->speed.y = speed*sin(angle);
	rotation = angle;
}

void Bullet::Update(float dt)
{
	bool collided = false;
	previousPos = box.pos;
	box.pos += speed*dt;

	hitbox.pos = Vec2(previousPos.x + 5, box.pos.y + 35);
	if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
	{
		collided = true;
		distanceLeft = 0;
	}

	hitbox.pos = Vec2(box.pos.x + 5, previousPos.y + 35);
	if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
	{
		collided = true;
		distanceLeft = 0;	
	}
	
	hitbox.pos = Vec2(box.pos.x + 5, box.pos.y + 35);
	
	if(!collided)
	{
		sp.Update(dt);
		distanceLeft -= speed.Mag()*dt;
	}
}

void Bullet::Render()
{
	int color[4] = COLOR_HITBOX;
	if (Config::HITBOX_MODE)
		hitbox.RenderFilledRect(color);

	sp.Render(box.pos.x, box.pos.y, rotation*180/M_PI);
}

bool Bullet::IsDead()
{
	return (distanceLeft <= 0);
}

void Bullet::NotifyCollision(GameObject &other, bool movement)
{
	if (targetsPlayer && other.Is("Eva")) {
		distanceLeft = 0;
	} else if ((!targetsPlayer) && (!other.Is("Eva"))) {
		distanceLeft = 0;
	}
}

bool Bullet::Is(std::string className)
{
	return ("Bullet" == className);
}

void Bullet::TakeDamage(float dmg) {}
