#pragma once

#include "EvaClass.h"
#include "Timer.h"

class EvaDecker : public EvaClass
{
public:
    EvaDecker();

    void Update(float dt);

    void Render(float x, float y);

    void SetCurrentState(int state);

    void Attack(int direction);

    void Die(Vec2 pos);

    bool IsAttacking();

    bool AttackReady();

private:
    Timer atkTimer;
    Timer atkCooldown;

};
