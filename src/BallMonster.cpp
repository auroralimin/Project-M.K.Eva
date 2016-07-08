#include "BallMonster.h"
#include "Config.h"
#include "Game.h"
#include "Animation.h"
#include "Bullet.h"

#define BALL_ANIMATIONS 3
#define AH_DIM_OFFSET_X 3
#define AH_DIM_OFFSET_Y 3
#define AH_POS_OFFSET_X box.dim.x/3
#define AH_POS_OFFSET_Y box.dim.y/2

BallMonster::BallMonster(Room *room, Vec2 pos) : previousPos(pos), hitTimer()
{
    this->room = room;
    std::string files[BALL_ANIMATIONS] = {
        "sprites/monsters/ball/BOLOTA_IDLE.png",
        "sprites/monsters/ball/BOLOTA_WARNING.png",
        "sprites/monsters/ball/BOLOTA_ATTACK.png"};
    int frameCounts[BALL_ANIMATIONS] = {6, 10, 6};
    float frameTimes[BALL_ANIMATIONS] = {0.15, 0.07, 0.3};
    animations = AnimationFSM(BALL_ANIMATIONS, files, frameCounts, frameTimes);

    box.pos = pos;
    box.dim = Vec2(animations.GetCurrentWidth(), animations.GetCurrentHeight());
    attackHitbox.dim = Vec2(box.dim.x/AH_DIM_OFFSET_X, box.dim.y/AH_DIM_OFFSET_Y);
    attackHitbox.pos = Vec2(box.pos.x + AH_POS_OFFSET_X, box.pos.y + AH_POS_OFFSET_Y);

    hitTimer.Restart();
    hp = 100;
    rotation = 0;
}

void BallMonster::Update(float dt)
{
    if (wasHit)
        hitTimer.Update(dt);
    if (hitTimer.Get() >= MONSTER_DAMAGE_DELAY){
        hitTimer.Restart();
        wasHit = false;
    }

    animations.Update(dt);
    attackHitbox.pos = Vec2(box.pos.x + AH_POS_OFFSET_X, box.pos.y + AH_POS_OFFSET_Y);
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
    if (!wasHit){
        hp -= dmg;
        wasHit = true;
    }
    if (IsDead()) {
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            box.pos, 0, "sprites/monsters/ball/BOLOTA_DEATH.png", 7,
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

