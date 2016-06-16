#include "Eva.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"
#include "Config.h"
#include "Animation.h"
#include "Bullet.h"
#include "EvaBase.h"
#include "EvaDecker.h"
#include "EvaGunslinger.h"
#include "EvaSamurai.h"

#include <iostream>

Eva::Eva(Vec2 pos)
{
    currentClass = BASE;

    evaClasses.emplace_back(new EvaBase());
    evaClasses.emplace_back(new EvaSamurai());
    evaClasses.emplace_back(new EvaDecker());
    evaClasses.emplace_back(new EvaGunslinger());
    box.pos = pos;
    box.dim = Vec2(evaClasses[currentClass]->animations.GetSpriteWidth(),
                   evaClasses[currentClass]->animations.GetSpriteHeight());
    hitbox.dim = Vec2(box.dim.x/2, box.dim.y/4);
    hitbox.pos = Vec2(box.pos.x + box.dim.x/4, box.pos.y + 3*box.dim.y/4);
    rotation = 0;
    hp = 100;
}

void Eva::Render()
{
    int color[4] = COLOR_HITBOX;
    if (Config::HITBOX_MODE)
        hitbox.RenderFilledRect(color);
    evaClasses[currentClass]->Render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y);
}

void Eva::Update(float dt)
{
    Vec2 previousPos = box.pos, speed = Vec2(0, 0);
    InputManager &manager = InputManager::GetInstance();

    if (!evaClasses[currentClass]->IsAttacking()) {
        if (manager.KeyPress(Q_KEY)) {
            if (currentClass == 0)
                currentClass = evaClasses.size() - 1;
            currentClass -= 1;
            if (currentClass < 1)
                currentClass = evaClasses.size() - 1;
        } else if (manager.KeyPress(E_KEY)) {
            currentClass += 1;
            if (currentClass > evaClasses.size() - 1)
                currentClass = 1;
        }
    }
    if (!evaClasses[currentClass]->IsAttacking() || currentClass == GUNSLINGER){
        if (manager.KeyPress(SPACEBAR)) // temporary suicide button
            TakeDamage(8000);

        if (manager.IsKeyDown(D_KEY))
            speed.x += 1;
        if (manager.IsKeyDown(A_KEY))
            speed.x -= 1;
        if (manager.IsKeyDown(S_KEY))
            speed.y += 1;
        if (manager.IsKeyDown(W_KEY))
            speed.y -= 1;

        if (!evaClasses[currentClass]->IsAttacking() || currentClass == GUNSLINGER)
            box.pos += speed.Normalize() * evaClasses[currentClass]->movSpeed * dt;

        if (speed.Normalize().y > 0 &&
                !(evaClasses[currentClass]->IsAttacking() &&
                  currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(MOVING_DOWN);
        if (speed.Normalize().y < 0 &&
                !(evaClasses[currentClass]->IsAttacking() &&
                  currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(MOVING_UP);
        if (speed.Normalize().x > 0 && speed.y == 0 &&
                !(evaClasses[currentClass]->IsAttacking() &&
                  currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(MOVING_RIGHT);
        if (speed.Normalize().x < 0 && speed.y == 0 &&
                !(evaClasses[currentClass]->IsAttacking() &&
                  currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(MOVING_LEFT);
        if (speed.GetModule() == 0 &&
                !(evaClasses[currentClass]->IsAttacking() &&
                  currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(IDLE);

        if (manager.IsKeyDown(UP_ARROW_KEY) &&
                evaClasses[currentClass]->AttackReady())
            currentClass == DECKER ?
                       evaClasses[currentClass]->Attack(Vec2(box.pos.x ,
                                                              box.pos.y),
                                                         ATTACKING_LEFT)
                      : evaClasses[currentClass]->Attack(Vec2(box.pos.x - 3*box.dim.x/8,
                                                  box.pos.y - box.dim.y/4),
                                             ATTACKING_UP);

        if (manager.IsKeyDown(DOWN_ARROW_KEY) &&
                evaClasses[currentClass]->AttackReady())
            currentClass == DECKER ?
                       evaClasses[currentClass]->Attack(Vec2(box.pos.x ,
                                                              box.pos.y),
                                                         ATTACKING_LEFT)
                      : evaClasses[currentClass]->Attack(Vec2(box.pos.x - box.dim.x/2,
                                                  box.pos.y + 3*box.dim.y/4),
                                             ATTACKING_DOWN);

        if (manager.IsKeyDown(LEFT_ARROW_KEY) &&
                evaClasses[currentClass]->AttackReady())
            currentClass == DECKER ?
                       evaClasses[currentClass]->Attack(Vec2(box.pos.x ,
                                                              box.pos.y),
                                                         ATTACKING_LEFT)
                      : evaClasses[currentClass]->Attack(Vec2(box.pos.x - box.dim.x,
                                                  box.pos.y + box.dim.y/4),
                                             ATTACKING_LEFT);

        if (manager.IsKeyDown(RIGHT_ARROW_KEY) &&
                evaClasses[currentClass]->AttackReady())
            currentClass == DECKER ?
                       evaClasses[currentClass]->Attack(Vec2(box.pos.x ,
                                                              box.pos.y),
                                                         ATTACKING_LEFT)
                      : evaClasses[currentClass]->Attack(Vec2(box.pos.x - box.dim.x/8,
                                                  box.pos.y + box.dim.y/4),
                                             ATTACKING_RIGHT);
    }

    hitbox.pos = Vec2(box.pos.x + box.dim.x/4, box.pos.y + 3*box.dim.y/4);
    if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
        box.pos.y = previousPos.y;

    hitbox.pos = Vec2(box.pos.x + box.dim.x/4, box.pos.y + 3*box.dim.y/4);
    if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
        box.pos.x = previousPos.x;

    hitbox.pos = Vec2(box.pos.x + box.dim.x/4, box.pos.y + 3*box.dim.y/4);
    evaClasses[currentClass]->Update(dt);

}

bool Eva::IsDead()
{
    return (hp <= 0);
}

void Eva::NotifyCollision(GameObject &other, bool movement)
{
	if (other.Is("Bullet")) {
		Bullet& bullet = (Bullet&) other;
		if (bullet.targetsPlayer) {
			TakeDamage(10);
		}
	} if (other.Is("Ball")) {
		TakeDamage(0);
	} else if (movement && (!other.Is("Ball"))) {
		box.pos = previousPos;
		if (other.Is("MekaBug")) {
			TakeDamage(5);
		}
	}
}

bool Eva::Is(std::string className)
{
    return (className == std::string("Eva"));
}

void Eva::TakeDamage(float dmg)
{
    hp -= dmg - (float)dmg*evaClasses[currentClass]->def/100;
    std::cout << hp << std::endl;
    if (IsDead()) {
        evaClasses[currentClass]->Die(box.GetCenter());
    }
}

std::string Eva::GetEvaDeath(void)
{
    return evaDeath;
}

