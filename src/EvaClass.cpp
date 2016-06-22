#include "EvaClass.h"

EvaClass::EvaClass(int nAnimations) : animations(nAnimations)
{
}

void EvaClass::Render(float x, float y)
{
    animations.Render(x, y);
}

bool EvaClass::IsAttacking(void)
{
    return isAttacking;
}

void EvaClass::SetCurrentState(int state)
{
    currentState = state;
    animations.SetCurrentState(state);
}

bool EvaClass::AttackReady(void)
{
    return atkReady;
}

