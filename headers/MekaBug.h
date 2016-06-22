#pragma once

#include "GameObject.h"
#include "AnimationFSM.h"
#include "Timer.h"

class MekaBug : public GameObject
{
  public:
    MekaBug(Vec2 pos, GameObject *focus);
    void Render();
    bool IsDead();
    void Update(float dt);
    void NotifyCollision(GameObject &other, bool movement);
    bool Is(std::string className);
    void TakeDamage(float dmg = 1);

  private:
    enum MekaBugMovement { RESTING, MOVING, TRAPED };
    enum MekaBugState { PASSIVE, AGRESSIVE };

    GameObject *focus;
    AnimationFSM animations;
    MekaBugMovement movState;
    Vec2 previousPos;
    bool stuck;

    void MovementAndAttack(float dt);
};

