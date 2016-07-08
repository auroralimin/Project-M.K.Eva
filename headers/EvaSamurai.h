#pragma once

#include "EvaClass.h"
#include "Timer.h"
#include "HealthBar.h"
#include "Minimap.h"

class EvaSamurai : public EvaClass
{
  public:
    EvaSamurai();

    void Update(float dt, float hp);

    void Attack(Vec2 pos, int direction);

    void Die(Vec2 pos);

    void Render(float x, float y);

  private:
    Timer atkTimer;
    Timer atkCooldown;

    HealthBar healthBar;
    Minimap minimap;
};

