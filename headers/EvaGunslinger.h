#pragma once

#include "EvaClass.h"
#include "Timer.h"

class EvaGunslinger : public EvaClass
{
  public:
    EvaGunslinger();

    void Update(float dt);

    void Attack(Vec2 pos, int direction);

    void Die(Vec2 pos);

  private:
    Timer atkTimer;
    Timer atkCooldown;
};

