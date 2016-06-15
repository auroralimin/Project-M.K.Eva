#pragma once

#include "EvaClass.h"

class EvaGunslinger : public EvaClass
{
public:
    EvaGunslinger();

    void Update(float dt);

    void Render(float x, float y);

    void SetCurrentState(int state);

    void Attack(int direction);

    void Die(Vec2 pos);

};
