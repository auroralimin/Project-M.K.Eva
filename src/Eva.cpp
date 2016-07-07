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

#define EVA_SPAWN_DELAY 0.5
#define HITBOX_DIM_OFFSET_X 2
#define HITBOX_DIM_OFFSET_Y 4
#define HITBOX_POS_OFFSET_X box.dim.x/4
#define HITBOX_POS_OFFSET_Y 3*box.dim.y/4
#define AH_DIM_OFFSET_X 3
#define AH_POS_OFFSET_X box.dim.x/3

Eva::Eva(Vec2 pos) : spawnDelayTimer()
{
    currentClass = BASE;

    evaClasses.emplace_back(new EvaBase());
    evaClasses.emplace_back(new EvaSamurai());
    evaClasses.emplace_back(new EvaDecker());
    evaClasses.emplace_back(new EvaGunslinger());
    box.pos = pos;
    box.dim = Vec2(evaClasses[currentClass]->animations.GetCurrentWidth(),
                   evaClasses[currentClass]->animations.GetCurrentHeight());
    hitbox.dim = Vec2(box.dim.x/HITBOX_DIM_OFFSET_X, box.dim.y/HITBOX_DIM_OFFSET_Y);
    hitbox.pos = Vec2(box.pos.x + HITBOX_POS_OFFSET_X, box.pos.y + HITBOX_POS_OFFSET_Y);
    attackHitbox.dim = Vec2(box.dim.x/AH_DIM_OFFSET_X, box.dim.y);
    attackHitbox.pos = Vec2(box.pos.x + AH_POS_OFFSET_X, box.pos.y);
    rotation = 0;
    hp = 100;
    spawnDelayTimer.Restart();
    doneSpawning = false;
}

void Eva::Render()
{
    int attackColor[4] = COLOR_ATTACK_HITBOX;
    if (Config::ATTACK_HITBOX_MODE)
        attackHitbox.RenderFilledRect(attackColor);

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
    if (spawnDelayTimer.Get() < EVA_SPAWN_DELAY)
        spawnDelayTimer.Update(dt);
    else
        doneSpawning = true;

    if (manager.KeyPress(SPACEBAR)) // temporary suicide button
        TakeDamage(8000);

    if (doneSpawning){
        previousPos = box.pos;

        //Check for attack input
        for (int i = 0; i < 4; i++) {
            if (manager.IsKeyDown(keys[i]) &&
                    evaClasses[currentClass]->AttackReady()) {
                if (currentClass == DECKER)
                    evaClasses[currentClass]->Attack(box.pos, 1);
                else
                    evaClasses[currentClass]->Attack(box.pos, i);
            }
        }

        //Check for class change input
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

        //Check for movement input
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

            //Update eva position
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

        }

        //Update hitboxes positions
        hitbox.pos = Vec2(box.pos.x + box.dim.x / 4, box.pos.y + 3 * box.dim.y / 4);
        if (Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
            box.pos.y = previousPos.y;

        hitbox.pos = Vec2(box.pos.x + box.dim.x / 4, box.pos.y + 3 * box.dim.y / 4);
        if (Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
            box.pos.x = previousPos.x;

        hitbox.pos = Vec2(box.pos.x + box.dim.x / 4, box.pos.y + 3 * box.dim.y / 4);

        attackHitbox.pos = Vec2(box.pos.x + box.dim.x/3, box.pos.y);

        //Update classes to make sure all cooldowns countdown
        for(uint i = 0; i < evaClasses.size(); i++) {
            evaClasses[i]->Update(dt, hp);
        }
    }
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
            TakeDamage(3);
    } else if (movement && (!other.Is("BallMonster"))) {
        box.pos = previousPos;
    }
}

bool Eva::Is(std::string className)
{
    return (className == std::string("Eva"));
}

void Eva::TakeDamage(float dmg)
{
    if(!(evaClasses[currentClass]->IsAttacking() && currentClass == DECKER))
        hp -= (dmg - (float)dmg * evaClasses[currentClass]->def / 100);
    if (Config::DEBUG)
        std::cout << "[Eva] hp: " << hp << std::endl;
    if (IsDead()) {
        evaDeath = std::string("Animation:sprites/eva/death/EVA-") +
                   classes[currentClass] + std::string("-DEATH.png");
        evaClasses[currentClass]->Die(box.pos);
    }
}

std::string Eva::GetEvaDeath(void)
{
    return evaDeath;
}

