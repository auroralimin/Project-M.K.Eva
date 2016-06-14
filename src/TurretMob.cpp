#include "TurretMob.h"
#include "Eva.h"
#include "Bullet.h"
#include "Game.h"
#include "Config.h"
#include <math.h>

#define IDLE 0
#define FRONT 1
#define FRONT_MIRROR 2
#define BACK 3
#define BACK_MIRROR 4

TurretMob::TurretMob(Vec2 pos)
{
	box.pos = pos;
	
	sprites[IDLE] = Sprite("sprites/monsters/turretmob/TurretMobIdle.png", 7, 0.3);
	sprites[FRONT] = Sprite("sprites/monsters/turretmob/TurretMobWalkFront.png", 8, 0.3);
	sprites[FRONT_MIRROR] = Sprite("sprites/monsters/turretmob/TurretMobWalkFrontMirror.png", 8, 0.3);
	sprites[BACK] = Sprite("sprites/monsters/turretmob/TurretMobWalkBack.png", 8, 0.3);
	sprites[BACK_MIRROR] = Sprite("sprites/monsters/turretmob/TurretMobWalkBackMirror.png", 8, 0.3);

	box.dim = Vec2(sprites[0].GetWidth(), sprites[0].GetHeight());
	hitbox.dim = Vec2(box.dim.x/2, box.dim.y/4);
	hitbox.pos = Vec2(box.pos.x + 35, box.pos.y + 80); 
	
	hp = 100;
	currentSprite = 0;
	state = TurretMobState::RESTING;
	rotation = 0;
	speed = Vec2(0, 0);
	previousPos = Vec2(0, 0);
}

TurretMob::~TurretMob()
{
}

void TurretMob::Render()
{
	int color[4] = COLOR_HITBOX;
	if (Config::HITBOX_MODE)
		hitbox.RenderFilledRect(color);

	sprites[currentSprite].Render(box.pos.x, box.pos.y, rotation);
}

bool TurretMob::IsDead()
{
	return (hp <= 0);
}

void TurretMob::Update(float dt)
{
	if(Eva::player != nullptr)
	{
		//looks at the player
		Vec2 lookVector = Eva::player->box.GetCenter();
		lookVector -= box.GetCenter();	
		if(lookVector.y < 0)
		{
			if(lookVector.x >= 0)
			{
				currentSprite = BACK;
			} else {
				currentSprite = BACK_MIRROR;
			}
		} else {
			if(lookVector.x >= 0)
			{
				currentSprite = FRONT_MIRROR;
			} else {
				currentSprite = FRONT;
			}
		}

		if(state == TurretMobState::RESTING)
		{
			currentSprite = IDLE;
			restTimer.Update(dt);
			if(restTimer.Get() >= Config::Rand(1.0, 3.5))
			{
				state = TurretMobState::MOVING;
				destination = Vec2(Config::Rand(100.0, 250.0), 0);
				float angle = Config::Rand(0, 2*M_PI);
				destination = destination.Rotate(angle);
				destination += box.pos;
			}
		}

		if(state == TurretMobState::MOVING)
		{
			if(box.pos.DistanceFromPoint(destination) <= 5)
			{
				box.pos = destination;
				restTimer.Restart();
				state = TurretMobState::RESTING;
				destination = Vec2(0, 0);
			} else {
				speed = destination;
				speed -= box.pos;
				speed = speed.Norm();
				speed *= 25*dt;
				previousPos = box.pos;
				box.pos += speed;
			}
			hitbox.pos = Vec2(previousPos.x + 35, box.pos.y + 80);
			if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
			{
				box.pos.y = previousPos.y;
				state = TurretMobState::RESTING;
				restTimer.Restart();
			}

			hitbox.pos = Vec2(box.pos.x + 35, previousPos.y + 80);
			if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
			{
				box.pos.x = previousPos.x;
				state = TurretMobState::RESTING;
				restTimer.Restart();
			}
		}
	
		hitbox.pos = Vec2(box.pos.x + 35, box.pos.y + 80);

		if(attackTimer.Get() >= Config::Rand(2.0, 6.0))
		{
			Vec2 evaPos = Eva::player->box.GetCenter();
			Vec2 boxVector = box.GetCenter();
			boxVector.y -= 25;
			boxVector.x -= 10;
			float angle = 0;

			evaPos -= box.GetCenter();
			angle = atan2(evaPos.y, evaPos.x);
			Bullet* b = new Bullet(boxVector, angle, 200, 1000, 
				"sprites/monsters/turret/penguinbullet.png", 4, 0.3, true);

			Game::GetInstance()->GetCurrentState().AddObject(b);

			attackTimer.Restart();
		}

	attackTimer.Update(dt);
	}

	sprites[currentSprite].Update(dt);
}

void TurretMob::NotifyCollision(GameObject &other)
{
}

bool TurretMob::Is(std::string className)
{
	return ("TurretMob" == className);
}

void TurretMob::TakeDamage(int dmg)
{
	hp -= dmg;
}
