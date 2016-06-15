#include "MekaBug.h"
#include "Eva.h"
#include "Config.h"
#include "Game.h"
#include "InputManager.h"
#include "Animation.h"
#include "Bullet.h"
#include "Collision.h"

MekaBug::MekaBug(Vec2 pos)
{
	box.pos = pos;

	sprites[0] = Sprite("sprites/monsters/mekabug/MEKABUG_SPRITESHEET.png", 6, 0.3);
	sprites[1] = Sprite("sprites/monsters/mekabug/MEKABUG_ATTACK_SPRITESHEET.png", 5, 0.3);

	box.dim = Vec2(sprites[0].GetWidth(), sprites[0].GetHeight());
	hitbox.dim = Vec2(box.dim.x, box.dim.y/2);
	hitbox.pos = Vec2(box.pos.x, box.pos.y + 35); 

	hp = 100;
	currentSprite = 0;
	state = MekaBugState::RESTING;
	rotation = 0;
	speed = Vec2(0, 0);
    stuck = false;
}

MekaBug::~MekaBug()
{
}

void MekaBug::Render()
{
	int color[4] = COLOR_HITBOX;
	if (Config::HITBOX_MODE)
		hitbox.RenderFilledRect(color);

	sprites[currentSprite].Render(box.pos.x, box.pos.y, rotation);
}

bool MekaBug::IsDead()
{
	return (hp <= 0);
}

void MekaBug::Update(float dt)
{
	InputManager &manager = InputManager::GetInstance();

	if (manager.KeyPress(L_KEY)) { // temporary suicide button
        TakeDamage(8000);
    }

	if(Eva::player != nullptr)
	{
		if(state == MekaBugState::RESTING)
		{
			restTimer.Update(dt);

			if(restTimer.Get() >= Config::Rand(1.0, 2.5))
			{
				state = MekaBugState::MOVING;
				currentSprite = 0;
			}
		}

		if(state == MekaBugState::MOVING)
		{
			Vec2 evaPos = Eva::player->box.GetCenter();
			if(Collision::IsColliding(Eva::player->hitbox, hitbox, 
				Eva::player->rotation, rotation))
			{
				state = MekaBugState::RESTING;
				speed = Vec2(0, 0);
				currentSprite = 1;
				restTimer.Restart();
			} else {
				speed = evaPos;
				speed -= box.pos;
				speed = speed.Norm();
				speed *= 40*dt;
				previousPos = box.pos;
                if (stuck) {
                    stuckTimer.Update(dt);
                    float angle = Config::Rand(M_PI, 2*M_PI);
                    box.pos += speed.Rotate(angle);
                    if (stuckTimer.Get() >= 0.5) {
                        stuck = false;
                        stuckTimer.Restart();
                    }
                } else {
				    box.pos += speed;
                }
			}

			hitbox.pos = Vec2(previousPos.x, box.pos.y + 35);
			if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
			{
				box.pos.y = previousPos.y;
				state = MekaBugState::RESTING;
				restTimer.Restart();
			}

			hitbox.pos = Vec2(box.pos.x, previousPos.y + 35);
			if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
			{
				box.pos.x = previousPos.x;
				state = MekaBugState::RESTING;
				restTimer.Restart();
			}

			hitbox.pos = Vec2(box.pos.x, box.pos.y + 35);
		}
	}
	sprites[currentSprite].Update(dt);
}

void MekaBug::NotifyCollision(GameObject &other, bool movement)
{
	if (other.Is("Bullet")) {
		Bullet& bullet = (Bullet&) other;
		if (!bullet.targetsPlayer) {
			TakeDamage(10);
		}
	} else if (movement && (!other.Is("Ball"))) {
		box.pos = previousPos;
        if (other.Is("MekaBug")) {
            stuck = true;
        }
	}
}

bool MekaBug::Is(std::string className)
{
	return ("MekaBug" == className);
}

void MekaBug::TakeDamage(float dmg)
{
	hp -= dmg;
	if(IsDead())
	{
		Game::GetInstance()->GetCurrentState().AddObject(new Animation(box.GetCenter(), 
			0, "sprites/monsters/mekabug/MEKABUG_DEATH.png", 3, 0.5, true));
	}
}
