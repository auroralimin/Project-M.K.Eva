#include "Ball.h"
#include "Config.h"
#include "Game.h"
#include "InputManager.h"
#include "Animation.h"
#include "Bullet.h"

#define BALL_ANIMATIONS 3

Ball::Ball(Vec2 pos) : animations(BALL_ANIMATIONS), previousPos(pos)
{
    std::string files[BALL_ANIMATIONS] = {
        "sprites/monsters/ball/BOLOTA_IDLE.png",
        "sprites/monsters/ball/BOLOTA_WARNING.png",
        "sprites/monsters/ball/BOLOTA_ATTACK.png"};
    int frameCounts[BALL_ANIMATIONS] = {6, 10, 6};
    float frameTimes[BALL_ANIMATIONS] = {0.3, 0.1, 0.3};
    for (int i = 0; i < BALL_ANIMATIONS; ++i) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }

	box.pos = pos;
	box.dim = Vec2(animations.GetCurrentWidth(), animations.GetCurrentHeight());

	hp = 100;
	rotation = 0;
}

void Ball::Render()
{
	int color[4] = COLOR_HITBOX;
	if (Config::HITBOX_MODE)
		hitbox.RenderFilledRect(color);

	animations.Render(box.pos.x, box.pos.y);
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
	animations.Update(dt);
}

void Ball::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR movement;

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

void Ball::SetCurrentState(int state)
{
    animations.SetCurrentState(state);
}

