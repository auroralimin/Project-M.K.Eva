#include "EvaBase.h"
#include "Config.h"

#define BASE_ANIMATIONS 5

EvaBase::EvaBase(void) : EvaClass()
{
    std::string tFiles[BASE_ANIMATIONS] = {
        "sprites/eva/movement/EVA-BASE-IDLE.png",
        "sprites/eva/movement/EVA-BASE-UP.png",
        "sprites/eva/movement/EVA-BASE-LEFT.png",
        "sprites/eva/movement/EVA-BASE-DOWN.png",
        "sprites/eva/movement/EVA-BASE-RIGHT.png"};
    files = tFiles;
    frameCounts = new int[BASE_ANIMATIONS]{6, 6, 6, 6, 6};
    frameTimes = new float[BASE_ANIMATIONS]{0.09, 0.09, 0.09, 0.09, 0.09};
    for (int i = 0; i < BASE_ANIMATIONS; i++)
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);

    movSpeed = 250;
    atk = def = atkSpeed = 1;
    isAttacking = atkReady = false;
}

void EvaBase::Update(float dt, float hp)
{
    UNUSED_VAR hp;
    animations.Update(dt);
}

void EvaBase::Attack(Vec2 pos, int direction)
{
    UNUSED_VAR pos;
    UNUSED_VAR direction;
    // do Nothing
}

void EvaBase::Die(Vec2 pos)
{
    UNUSED_VAR pos;
    // do nothing
}

