#include "Turret.h"
#include "Eva.h"
#include "Bullet.h"
#include "Game.h"

float Rand(float fMin, float fMax) {
			float f = (float)rand() / RAND_MAX;
			return fMin + f*(fMax - fMin);
}

Turret::Turret(Vec2 pos) : sp("sprites/alien.png")
{
	box.pos = pos;
	box.dim.x = sp.GetWidth();
	box.dim.y = sp.GetHeight();
}

Turret::~Turret(){}

void Turret::Render()
{
	sp.Render(box.pos.x, box.pos.y, rotation);
}

bool Turret::IsDead()
{
	if(hp <= 0)
		return true;

	return false;
}

void Turret::Update(float dt)
{	
	if(timer.Get() >= 2.5f)
	{
		float pattern = Rand(0.0, 100.0);
		if(pattern <= 30.0)
		{
			ShootPattern2();
		} else {
			ShootPattern1();
		}
		timer.Restart();
	}

	timer.Update(dt);
}

void Turret::NotifyCollision(GameObject &other)
{

}

bool Turret::Is(std::string className)
{
	return ("Turret" == className);
}

void Turret::TakeDamage(int dmg)
{
	hp -= dmg;
}

void Turret::ShootPattern1()
{
	if(Eva::player != nullptr)
	{
		Vec2 evaPos = Eva::player->box.GetCenter();
		float angle = 0;

		evaPos -= box.GetCenter();
		angle = atan2(evaPos.y, evaPos.x);
		Bullet* b1 = new Bullet(box.GetCenter(), angle, 200, 1000, 
			"sprites/penguinbullet.png", 4, 0.3, true);

		Bullet* b2 = new Bullet(box.GetCenter(), angle + 0.3, 200, 1000,
			"sprites/penguinbullet.png", 4, 0.3, true);

		Bullet* b3 = new Bullet(box.GetCenter(), angle - 0.3, 200, 1000,
			"sprites/penguinbullet.png", 4, 0.3, true);

		Game::GetInstance()->GetCurrentState().AddObject(b1);
		Game::GetInstance()->GetCurrentState().AddObject(b2);
		Game::GetInstance()->GetCurrentState().AddObject(b3);
	}
}

void Turret::ShootPattern2()
{
	if(Eva::player != nullptr)
	{
		for(int i = 0; i < 15; i++)
		{
			Bullet* b = new Bullet(box.GetCenter(), 2*M_PI*(i+1)/15, 200, 1000, 
			"sprites/penguinbullet.png", 4, 0.3, true);
			
			Game::GetInstance()->GetCurrentState().AddObject(b);
		}
	}
}
