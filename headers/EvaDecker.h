#pragma once

#include "EvaClass.h"
#include "Timer.h"
#include "HealthBar.h"

class EvaDecker : public EvaClass
{
  public:
    EvaDecker();

    void Update(float dt, float hp);

    void Attack(Vec2 pos, int direction);

    void Die(Vec2 pos);

    void Render(float x, float y);

  private:
    Timer atkTimer;
    Timer atkCooldown;
    bool atkStarted;
    Vec2 atkPos;

    void Shockwave(Vec2 pos);

    HealthBar healthBar;
};

