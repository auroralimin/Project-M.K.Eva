#pragma once

#include "EvaClass.h"
#include "Timer.h"

class EvaDecker : public EvaClass
{
    public:
        EvaDecker();

        void Update(float dt);

        void Attack(Vec2 pos, int direction);

        void Die(Vec2 pos);

    private:
        Timer atkTimer;
        Timer atkCooldown;
        bool atkStarted;
        Vec2 atkPos;

        void Shockwave(Vec2 pos);
};

