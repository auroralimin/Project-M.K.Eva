#pragma once

#include "EvaClass.h"

class EvaBase : public EvaClass
{
    public:
        EvaBase(void);

        void Update(float dt);

        void Attack(Vec2 pos, int direction);

        void Die(Vec2 pos);
};

