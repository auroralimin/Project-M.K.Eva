#include "BallMonster.h"
#include "Config.h"
#include "Game.h"
#include "InputManager.h"
#include "Animation.h"
#include "Bullet.h"

#define BALL_ANIMATIONS 3

BallMonster::BallMonster(Room *room, Vec2 pos) : previousPos(pos)
{
    this->room = room;
    std::string files[BALL_ANIMATIONS] = {
        "sprites/monsters/ball/BOLOTA_IDLE.png",
        "sprites/monsters/ball/BOLOTA_WARNING.png",
        "sprites/monsters/ball/BOLOTA_ATTACK.png"};
    int frameCounts[BALL_ANIMATIONS] = {6, 10, 6};
    float frameTimes[BALL_ANIMATIONS] = {0.3, 0.1, 0.3};
    animations = AnimationFSM(BALL_ANIMATIONS, files, frameCounts, frameTimes);

    box.pos = pos;
    box.dim = Vec2(animations.GetCurrentWidth(), animations.GetCurrentHeight());
    attackHitbox.dim = Vec2(box.dim.x/3, box.dim.y/3);
    attackHitbox.pos = Vec2(box.pos.x + box.dim.x/3, box.pos.y + box.dim.y/2);

    hp = 100;
    rotation = 0;
}

void BallMonster::Update(float dt)
{
    InputManager &manager = InputManager::GetInstance();

    if (manager.KeyPress(K_KEY)) { // temporary suicide button
        TakeDamage(8000);
    }
    animations.Update(dt);
    attackHitbox.pos = Vec2(box.pos.x + box.dim.x/3, box.pos.y + box.dim.y/2);
}

void BallMonster::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR movement;

    if (other.Is("Bullet") || other.Is("Attack")) {
        Bullet &bullet = (Bullet &)other;
        if (!bullet.targetsPlayer) {
            TakeDamage(10);
        }
    }
}

bool BallMonster::Is(std::string className)
{
    return ("BallMonster" == className);
}

void BallMonster::TakeDamage(float dmg)
{
    hp -= dmg;
    if (IsDead()) {
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            box.GetCenter(), 0, "sprites/monsters/ball/BOLOTA_DEATH.png", 7,
            0.2, true));
    }
}

bool BallMonster::IsInsideWall()
{
    if (Game::GetInstance() != nullptr) {
        return Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this);
    }

    return false;
}

void BallMonster::SetCurrentState(int state)
{
    animations.SetCurrentState(state);
}

