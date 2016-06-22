#pragma once

#include "GameObject.h"
#include "AnimationFSM.h"

/*****************************************
 * The representation of the turret enemy
 ****************************************/

class Turret : public GameObject
{
  public:
    Turret(Vec2 pos, GameObject *focus);
    void Render(void);
    bool IsDead(void);
    void Update(float dt);
    void NotifyCollision(GameObject &other, bool movement);
    bool Is(std::string className);
    void TakeDamage(float dmg = 1);

  private:
    GameObject *focus;
    AnimationFSM animations;

    void ShootPattern1(void);
    void ShootPattern2(void);
};

