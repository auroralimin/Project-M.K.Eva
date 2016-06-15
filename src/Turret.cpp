#include "Turret.h"
#include "Eva.h"
#include "Bullet.h"
#include "Game.h"
#include "Config.h"
#include "Animation.h"
#include "InputManager.h"

Turret::Turret(Vec2 pos) : sp("sprites/monsters/turret/alien.png")
{
	box.pos = pos;
	box.dim.x = sp.GetWidth();
	box.dim.y = sp.GetHeight();
	hp = 100;
	rotation = 0;
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
	InputManager &manager = InputManager::GetInstance();

	if (manager.KeyPress(H_KEY)) { // temporary suicide button
        TakeDamage(8000);
    }

	if(Eva::player != nullptr)
	{
		if(timer.Get() >= 2.5f)
		{
			ShootPattern1();
			timer.Restart();
		}
	}

	timer.Update(dt);
}

void Turret::NotifyCollision(GameObject &other, bool movement)
{
	if (other.Is("Bullet")) {
		Bullet& bullet = (Bullet&) other;
		if (!bullet.targetsPlayer) {
			TakeDamage(10);
		}
	}
}

bool Turret::Is(std::string className)
{
	return ("Turret" == className);
}

void Turret::TakeDamage(float dmg)
{
	hp -= dmg;
	if(IsDead())
	{
		Game::GetInstance()->GetCurrentState().AddObject(new Animation(box.GetCenter(), 
			0, "sprites/monsters/turret/penguindeath.png", 5, 0.3, true));
		ShootPattern2();
	}
}

void Turret::ShootPattern1()
{
	Vec2 evaPos = Eva::player->box.GetCenter();
	float angle = 0;

	evaPos -= box.GetCenter();
	angle = atan2(evaPos.y, evaPos.x);
	Bullet* b1 = new Bullet(box.GetCenter(), angle, 200, 1000, 
		"sprites/monsters/turret/penguinbullet.png", 4, 0.3, true);

	Bullet* b2 = new Bullet(box.GetCenter(), angle + 0.3, 200, 1000,
		"sprites/monsters/turret/penguinbullet.png", 4, 0.3, true);

	Bullet* b3 = new Bullet(box.GetCenter(), angle - 0.3, 200, 1000,
		"sprites/monsters/turret/penguinbullet.png", 4, 0.3, true);

	Game::GetInstance()->GetCurrentState().AddObject(b1);
	Game::GetInstance()->GetCurrentState().AddObject(b2);
	Game::GetInstance()->GetCurrentState().AddObject(b3);
}

void Turret::ShootPattern2()
{
	for(int i = 0; i < 15; i++)
	{
		Bullet* b = new Bullet(box.GetCenter(), 2*M_PI*(i+1)/15, 200, 1000, 
			"sprites/monsters/turret/penguinbullet.png", 4, 0.3, true);
			
		Game::GetInstance()->GetCurrentState().AddObject(b);
	}
}
