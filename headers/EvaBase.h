#pragma once

#include "EvaClass.h"

class EvaBase : public EvaClass
{
public:
    EvaBase();

    void Update(float dt);

    void Render(float x, float y);

    void SetCurrentState(int state);

    void Attack(int direction);

    void Die(Vec2 pos);

};
