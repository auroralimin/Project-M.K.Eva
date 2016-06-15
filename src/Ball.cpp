#include "Ball.h"
#include "Eva.h"
#include "Config.h"
#include "Game.h"
#include "InputManager.h"
#include "Animation.h"
#include "Bullet.h"
#include <math.h>

#define IDLE 0
#define ATTACK 1
#define WAR 2

Ball::Ball(Vec2 pos)
{
	box.pos = pos;

	sprites[IDLE] = Sprite("sprites/monsters/ball/BOLOTA_IDLE.png", 6, 0.3);
	sprites[ATTACK] = Sprite("sprites/monsters/ball/BOLOTA_ATTACK.png", 6, 0.3);
	sprites[WAR] = Sprite("sprites/monsters/ball/BOLOTA_WARNING.png", 10, 0.1);

	box.dim = Vec2(sprites[0].GetWidth(), sprites[0].GetHeight());

	hitbox.dim = Vec2(box.dim.x/3, box.dim.y/5);
	hitbox.pos = Vec2(box.pos.x + 43, box.pos.y + 110); 

	hp = 100;
	currentSprite = 0;
	state = BallState::RESTING;
	rotation = 0;
	speed = Vec2(0, 0);
	attackFinished = false;
}

Ball::~Ball()
{
}

void Ball::Render()
{
	int color[4] = COLOR_HITBOX;
	if (Config::HITBOX_MODE)
		hitbox.RenderFilledRect(color);

	sprites[currentSprite].Render(box.pos.x, box.pos.y, rotation);
}

bool Ball::IsDead()
{
	return (hp <= 0);
}

void Ball::Update(float dt)
{
	InputManager &manager = InputManager::GetInstance();

	if (manager.KeyPress(K_KEY)) { // temporary suicide button
        TakeDamage(8000);
    }

	if(Eva::player != nullptr)
	{
		if(attackTimer.Get() >= 1.8)
		{
			attackFinished = true;
			attackTimer.Restart();
			sprites[ATTACK].SetFrame(0);
		}

		if(state == BallState::RESTING)
		{
			restTimer.Update(dt);

			if(restTimer.Get() >= Config::Rand(1.0, 2.5))
			{
				if(box.GetCenter().DistanceFromPoint(Eva::player->box.GetCenter()) >= 250)
				{
					state = BallState::WARNING;
				} else {
					currentSprite = IDLE;
					state = BallState::MOVING;
				}

				restTimer.Restart();
			}
		}

		if(state == BallState::WARNING)
		{
			currentSprite = WAR;
			warningTimer.Update(dt);
			if(warningTimer.Get() >= 1.8)
			{
				Vec2 teleportPos = Vec2(40, 0);
				float angle = Config::Rand(0, 2*M_PI);
				teleportPos = teleportPos.Rotate(angle);
				teleportPos += Eva::player->box.GetCenter();;
				teleportPos.x -= sprites[currentSprite].GetWidth()/2;
				teleportPos.y -= sprites[currentSprite].GetHeight()/2;
				previousPos = box.pos;
				box.pos = teleportPos;
				warningTimer.Restart();
				state = BallState::MOVING;
			}
		}

		if(state == BallState::MOVING)
		{
			if(box.GetCenter().DistanceFromPoint(Eva::player->box.GetCenter()) <= 50)
			{
				currentSprite = ATTACK;
				speed = Vec2(0, 0);
				attackFinished = false;

			} else if(attackFinished && 
				(box.GetCenter().DistanceFromPoint(Eva::player->box.GetCenter()) < 250)) {
				currentSprite = IDLE;
				speed = Eva::player->box.GetCenter();
				speed -= box.GetCenter();
				speed = speed.Norm();
				speed *= 10*dt;
				previousPos = box.pos;
				box.pos += speed;
				attackTimer.Restart();

			} else if(attackFinished) {
				currentSprite = IDLE;
				state = BallState::WARNING;
				attackTimer.Restart();
			}

			hitbox.pos = Vec2(previousPos.x + 43, box.pos.y + 110);
			if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
			{
				box.pos.y = previousPos.y;
				state = BallState::RESTING;
			}

			hitbox.pos = Vec2(box.pos.x + 43, previousPos.y + 110);
			if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
			{
				box.pos.x = previousPos.x;
				state = BallState::RESTING;
			}
			hitbox.pos = Vec2(box.pos.x + 43, box.pos.y + 110);
		}
		
		attackTimer.Update(dt);
	}

	sprites[currentSprite].Update(dt);
}

void Ball::NotifyCollision(GameObject &other, bool movement)
{
	if (other.Is("Bullet")) {
		Bullet& bullet = (Bullet&) other;
		if (!bullet.targetsPlayer) {
			TakeDamage(10);
		}
	} else if (movement && (!other.Is("Eva"))) {
		box.pos = previousPos;
	}
}

bool Ball::Is(std::string className)
{
	return ("Ball" == className);
}

void Ball::TakeDamage(float dmg)
{
	hp -= dmg;
	if(IsDead())
	{
		Game::GetInstance()->GetCurrentState().AddObject(new Animation(box.GetCenter(), 
			0, "sprites/monsters/ball/BOLOTA_DEATH.png", 7, 0.2, true));
	}
}

bool Ball::IsInsideWall()
{
	return Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this);
}
