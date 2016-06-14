#include "MekaBug.h"
#include "Eva.h"

MekaBug::MekaBug(Vec2 pos)
{
	box.pos = pos;

	sprites[0] = Sprite("sprites/monsters/mekabug/MEKABUG_SPRITESHEET.png", 6, 0.3);
	sprites[1] = Sprite("sprites/monsters/mekabug/MEKABUG_ATTACK_SPRITESHEET.png", 5, 0.3);

	box.dim = Vec2(sprites[0].GetWidth(), sprites[0].GetHeight());
	hp = 100;
	currentSprite = 0;
	state = MekaBugState::RESTING;
	rotation = 0;
	speed = Vec2(0, 0);
}

MekaBug::~MekaBug()
{
}

void MekaBug::Render()
{
	sprites[currentSprite].Render(box.pos.x, box.pos.y, rotation);
}

bool MekaBug::IsDead()
{
	return (hp <= 0);
}

void MekaBug::Update(float dt)
{
	if(Eva::player != nullptr)
	{
		if(state == MekaBugState::RESTING)
		{
			restTimer.Update(dt);

			if(restTimer.Get() >= 2.5f)
			{
				state = MekaBugState::MOVING;
				currentSprite = 0;
			}
		}

		if(state == MekaBugState::MOVING)
		{
			Vec2 evaPos = Eva::player->box.GetCenter();
			Vec2 boxVector = box.GetCenter();

			if(boxVector.DistanceFromPoint(evaPos) <= 20)
			{
				state = MekaBugState::RESTING;
				speed = Vec2(0, 0);
				currentSprite = 1;
				restTimer.Restart();
			} else {
				speed = evaPos;
				speed -= boxVector;
				speed = speed.Norm();
				speed *= 50*dt;
				box.pos += speed;
			}
		}
	}
	sprites[currentSprite].Update(dt);
}

void MekaBug::NotifyCollision(GameObject &other)
{
}

bool MekaBug::Is(std::string className)
{
	return ("MekaBug" == className);
}

void MekaBug::TakeDamage(int dmg)
{
	hp -= dmg;
}
