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

    void Attack(Vec2 pos, int direction);

    void Die(Vec2 pos);

    bool IsAttacking();

    bool AttackReady();

private:
    Timer atkTimer;
    Timer atkCooldown;
    bool atkStarted;
    void Shockwave(Vec2 pos);
    Vec2 atkPos;
};
