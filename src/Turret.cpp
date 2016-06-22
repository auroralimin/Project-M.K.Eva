#include "Turret.h"
#include "Eva.h"
#include "Bullet.h"
#include "Game.h"
#include "Config.h"
#include "Timer.h"
#include "Animation.h"
#include "InputManager.h"

#define TURRET_ANIMATIONS 1

Turret::Turret(Vec2 pos, GameObject *focus) :
    focus(focus), animations(TURRET_ANIMATIONS)
{
    std::string files[TURRET_ANIMATIONS] = {
        "sprites/monsters/turret/alien.png"};
    int frameCounts[TURRET_ANIMATIONS] = {1};
    float frameTimes[TURRET_ANIMATIONS] = {300.0};
    for (int i = 0; i < TURRET_ANIMATIONS; i++) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }

	box.pos = pos;
	box.dim = Vec2(animations.GetCurrentWidth(), animations.GetCurrentHeight());
	hp = 100;
	rotation = 0;
}

void Turret::Render(void)
{
	animations.Render(box.pos.x, box.pos.y);
}

bool Turret::IsDead(void)
{
	if(hp <= 0)
		return true;

	return false;
}

void Turret::Update(float dt)
{	
    static Timer timer = Timer();
	InputManager &manager = InputManager::GetInstance();

	if (manager.KeyPress(H_KEY)) { // temporary suicide button
        TakeDamage(8000);
    }

    if(timer.Get() >= 2.5f)
    {
        ShootPattern1();
        timer.Restart();
    }

    animations.Update(dt);
    timer.Update(dt);
}

void Turret::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR movement;

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

void Turret::ShootPattern1(void)
{
    const int nBullets = 3;
    Vec2 evaPos = focus->box.GetCenter();
    float angle = 0;

    evaPos -= box.GetCenter();
    angle = atan2(evaPos.y, evaPos.x);
    float anglesOffsets[nBullets] = {0.0, 0.3, -0.3};
    
    for (int i = 0; i < nBullets; ++i)
        Game::GetInstance()->GetCurrentState().AddObject(
                new Bullet(box.GetCenter(),
                    angle + anglesOffsets[i], 200, 1000, 
                    "sprites/monsters/turret/penguinbullet.png",
                    Vec2(-15, -15), Vec2(30, 30), 4, 0.3, true));
}

void Turret::ShootPattern2(void)
{
    for(int i = 0; i < 15; i++)
    {
        Bullet* b = new Bullet(box.GetCenter(), 2*M_PI*(i+1)/15, 200, 1000, 
                "sprites/monsters/turret/penguinbullet.png",
                Vec2(-15, -15), Vec2(30, 30), 4, 0.3, true);

        Game::GetInstance()->GetCurrentState().AddObject(b);
    }
}

