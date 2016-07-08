#pragma once

#include "Monster.h"
#include "Timer.h"

class TurretMobMonster : public Monster
{
  public:
    TurretMobMonster(Room *room, Vec2 pos, GameObject *focus);
    void Update(float dt);
    void NotifyCollision(GameObject &other, bool movement);
    bool Is(std::string className);
    void TakeDamage(float dmg = 1);

  private:
    enum TurretMobMonsterMovement { RESTING, MOVING, TRAPED };
    enum TurretMobMonsterState { IDLE, FRONT, FRONT_MIRROR, BACK, BACK_MIRROR };

    GameObject *focus;
    TurretMobMonsterMovement movementMode;
    Vec2 previousPos, destination;
    Timer restTimer;
    Timer hitTimer;
    bool wasHit;

    void LookAtFocus(void);
    void Movement(float dt);
    void Attack(float dt);
};

