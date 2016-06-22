#pragma once

#include "GameObject.h"
#include "AnimationFSM.h"

class Ball : public GameObject
{
  public:
    Ball(Vec2 pos);
    void Render();
    bool IsDead();
    void Update(float dt);
    void NotifyCollision(GameObject &other, bool movement);
    bool Is(std::string className);
    void TakeDamage(float dmg = 1);
    bool IsInsideWall();
    void SetCurrentState(int state);

  private:
    AnimationFSM animations;
    Vec2 previousPos;
};

