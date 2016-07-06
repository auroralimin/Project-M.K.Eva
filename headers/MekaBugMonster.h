#pragma once

#include "Monster.h"
#include "Timer.h"

class MekaBugMonster : public Monster
{
  public:
    MekaBugMonster(Room *room, Vec2 pos, GameObject *focus);
    void Update(float dt);
    void NotifyCollision(GameObject &other, bool movement);
    bool Is(std::string className);
    void TakeDamage(float dmg = 1);

  private:
    enum MekaBugMonsterMovement { RESTING, MOVING, TRAPED };
    enum MekaBugMonsterState { PASSIVE, AGRESSIVE };

    GameObject *focus;
    MekaBugMonsterMovement movState;
    Vec2 previousPos;
    bool stuck;

    void MovementAndAttack(float dt);
};

