#include "EvaBase.h"

#define BASE_ANIMATIONS 5

EvaBase::EvaBase() : EvaClass(BASE_ANIMATIONS)
{
    std::string tFiles[BASE_ANIMATIONS] = { std::string("sprites/eva/movement/EVA-BASE-IDLE.png"),
              std::string("sprites/eva/movement/EVA-BASE-UP.png"),
              std::string("sprites/eva/movement/EVA-BASE-DOWN.png"),
              std::string("sprites/eva/movement/EVA-BASE-LEFT.png"),
              std::string("sprites/eva/movement/EVA-BASE-RIGHT.png"),
            };
    files = tFiles;
    frameCounts = new int[BASE_ANIMATIONS] {6, 6, 6, 6, 6};
    frameTimes = new float[BASE_ANIMATIONS] {0.08, 0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < BASE_ANIMATIONS; i++) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }
    movSpeed = 200;
    atk = 1;
    def = 1;
    atkSpeed = 1;
    isAttacking = false;
    atkReady = false;
}

void EvaBase::Update(float dt)
{
    //TODO: update possible timers
    animations.Update(dt);
}

void EvaBase::Render(float x, float y)
{
    animations.Render(x, y);
}

void EvaBase::SetCurrentState(int state)
{
    currentState = state;
    animations.SetCurrentState(state);
}

void EvaBase::Attack(Vec2 pos, int direction)
{
    //Do Nothing
}

void EvaBase::Die(Vec2 pos)
{
    //Do nothing
}

bool EvaBase::IsAttacking()
{
    return false;
}

bool EvaBase::AttackReady()
{
    return false;
}

