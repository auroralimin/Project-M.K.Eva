#include "Ball.h"
#include "Config.h"
#include "Game.h"
#include "InputManager.h"
#include "Animation.h"
#include "Bullet.h"

Ball::Ball(Vec2 pos)
{
	box.pos = pos;
	previousPos = pos;

	sprites[0] = Sprite("sprites/monsters/ball/BOLOTA_IDLE.png", 6, 0.3);
	sprites[1] = Sprite("sprites/monsters/ball/BOLOTA_ATTACK.png", 6, 0.3);
	sprites[2] = Sprite("sprites/monsters/ball/BOLOTA_WARNING.png", 10, 0.1);

	box.dim = Vec2(sprites[0].GetWidth(), sprites[0].GetHeight());

	hitbox.dim = Vec2(box.dim.x/3, box.dim.y/5);
	hitbox.pos = Vec2(box.pos.x + 43, box.pos.y + 110); 

	hp = 100;
	currentSprite = 0;
	rotation = 0;
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
	sprites[currentSprite].Update(dt);
	hitbox.pos = Vec2(box.pos.x + 43, box.pos.y + 110);
}

void Ball::NotifyCollision(GameObject &other, bool movement)
{
	if (other.Is("Bullet")) {
		Bullet& bullet = (Bullet&) other;
		if (!bullet.targetsPlayer) {
			TakeDamage(10);
		}
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
	if (Game::GetInstance() != nullptr) {
		return Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this);
	}

	return false;
}

void Ball::SetCurrentSprite(int sprite)
{
	currentSprite = sprite;
}
