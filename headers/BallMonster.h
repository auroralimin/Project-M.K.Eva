#pragma once

#include "Monster.h"
#include "Timer.h"

class BallMonster : public Monster
{
  public:
    BallMonster(Room *room, Vec2 pos);
    void Update(float dt);
    void NotifyCollision(GameObject &other, bool movement);
    bool Is(std::string className);
    void TakeDamage(float dmg = 1);
    bool IsInsideWall();
    void SetCurrentState(int state);

  private:
    Vec2 previousPos;
    Timer hitTimer;
    bool wasHit;
};

