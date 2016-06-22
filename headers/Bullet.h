#pragma once

#include "GameObject.h"
#include "Sprite.h"

class Bullet : public GameObject
{
  public:
    Bullet(Vec2 pos, float angle, float speed, float maxDistance,
           std::string sprite, Vec2 hitboxOffset, Vec2 hitboxDim,
           int frameCount = 1, float frameTime = 1, bool targetsPlayer = false);
    void Render();
    bool IsDead();
    void Update(float dt);
    void NotifyCollision(GameObject &other, bool movement);
    bool Is(std::string className);
    void TakeDamage(float dmg = 1);

    bool targetsPlayer;

  private:
    Sprite sp;
    Vec2 speed, hitboxOffset, previousPos;
    float distanceLeft;
};

