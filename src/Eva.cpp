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
    box.dim = Vec2(evaClasses[currentClass]->animations.GetCurrentWidth(),
                   evaClasses[currentClass]->animations.GetCurrentHeight());
    hitbox.dim = Vec2(box.dim.x / 2, box.dim.y / 4);
    hitbox.pos = Vec2(box.pos.x + box.dim.x / 4, box.pos.y + 3 * box.dim.y / 4);
    rotation = 0;
    hp = 100;
}

void Eva::Render()
{
    int color[4] = COLOR_HITBOX;
    if (Config::HITBOX_MODE)
        hitbox.RenderFilledRect(color);
    evaClasses[currentClass]->Render(box.pos.x - Camera::pos.x,
                                     box.pos.y - Camera::pos.y);
}

void Eva::Update(float dt)
{
    const int keys[4] = {UP_ARROW_KEY, LEFT_ARROW_KEY, DOWN_ARROW_KEY,
                         RIGHT_ARROW_KEY};
    Vec2 speed = Vec2(0, 0);
    InputManager &manager = InputManager::GetInstance();

    if (manager.KeyPress(SPACEBAR)) // temporary suicide button
        TakeDamage(8000);

    previousPos = box.pos;
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
    if (!evaClasses[currentClass]->IsAttacking() ||
        currentClass == GUNSLINGER) {
        if (manager.IsKeyDown(D_KEY))
            speed.x += 1;
        if (manager.IsKeyDown(A_KEY))
            speed.x -= 1;
        if (manager.IsKeyDown(S_KEY))
            speed.y += 1;
        if (manager.IsKeyDown(W_KEY))
            speed.y -= 1;

        speed = speed.Normalize();
        if (!evaClasses[currentClass]->IsAttacking() ||
            currentClass == GUNSLINGER)
            box.pos += speed * evaClasses[currentClass]->movSpeed * dt;

        if (speed.y > 0 &&
            !(evaClasses[currentClass]->IsAttacking() &&
              currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(MOVING_DOWN);
        if (speed.y < 0 &&
            !(evaClasses[currentClass]->IsAttacking() &&
              currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(MOVING_UP);
        if (speed.x > 0 && speed.y == 0 &&
            !(evaClasses[currentClass]->IsAttacking() &&
              currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(MOVING_RIGHT);
        if (speed.x < 0 && speed.y == 0 &&
            !(evaClasses[currentClass]->IsAttacking() &&
              currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(MOVING_LEFT);
        if (speed.GetModule() == 0 &&
            !(evaClasses[currentClass]->IsAttacking() &&
              currentClass == GUNSLINGER))
            evaClasses[currentClass]->SetCurrentState(IDLE);

        for (int i = 0; i < 4; i++) {
            if (manager.IsKeyDown(keys[i]) &&
                evaClasses[currentClass]->AttackReady()) {
                if (currentClass == DECKER)
                    evaClasses[currentClass]->Attack(box.pos, 1);
                else
                    evaClasses[currentClass]->Attack(box.pos, i);
            }
        }
    }

    hitbox.pos = Vec2(box.pos.x + box.dim.x / 4, box.pos.y + 3 * box.dim.y / 4);
    if (Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
        box.pos.y = previousPos.y;

    hitbox.pos = Vec2(box.pos.x + box.dim.x / 4, box.pos.y + 3 * box.dim.y / 4);
    if (Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
        box.pos.x = previousPos.x;

    hitbox.pos = Vec2(box.pos.x + box.dim.x / 4, box.pos.y + 3 * box.dim.y / 4);
    evaClasses[currentClass]->Update(dt);
}

bool Eva::IsDead()
{
    return (hp <= 0);
}

void Eva::NotifyCollision(GameObject &other, bool movement)
{
    if (other.Is("Bullet")) {
        Bullet &bullet = (Bullet &)other;
        if (bullet.targetsPlayer)
            TakeDamage(10);
    } else if (other.Is("Ball")) {
        TakeDamage(0);
    } else if (other.Is("MonsterBallManager")) {
        TakeDamage(1);
    } else if (movement && (!other.Is("Ball"))) {
        box.pos = previousPos;
        if (other.Is("MekaBug"))
            TakeDamage(5);
    }
}

bool Eva::Is(std::string className)
{
    return (className == std::string("Eva"));
}

void Eva::TakeDamage(float dmg)
{
    hp -= (dmg - (float)dmg * evaClasses[currentClass]->def / 100);
    if (Config::DEBUG)
        std::cout << "[Eva] hp: " << hp << std::endl;
    if (IsDead()) {
        evaDeath = std::string("Animation:sprites/eva/death/EVA-") +
                   classes[currentClass] + std::string("-DEATH.png");
        evaClasses[currentClass]->Die(box.GetCenter());
    }
}

std::string Eva::GetEvaDeath(void)
{
    return evaDeath;
}

