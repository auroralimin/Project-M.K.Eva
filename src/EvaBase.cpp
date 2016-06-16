#include "EvaBase.h"

EvaBase::EvaBase() : EvaClass(5)
{
    std::string tFiles[5] = { std::string("sprites/eva/movement/EVA-BASE-IDLE.png"),
              std::string("sprites/eva/movement/EVA-BASE-UP.png"),
              std::string("sprites/eva/movement/EVA-BASE-DOWN.png"),
              std::string("sprites/eva/movement/EVA-BASE-LEFT.png"),
              std::string("sprites/eva/movement/EVA-BASE-RIGHT.png"),
            };
    files = tFiles;
    frameCounts = new int[5] {6, 6, 6, 6, 6};
    frameTimes = new float[5] {0.08, 0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < 5; i++) {
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

void EvaBase::Attack(int direction)
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

