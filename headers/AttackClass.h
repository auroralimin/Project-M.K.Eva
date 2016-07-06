#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

class AttackClass : public GameObject
{
  public:
    AttackClass(Vec2 pos, Vec2 hitboxOffset, Vec2 hitboxDim, float dmg,
                std::string sprite = "", int frameCount = 1, float frameTime = 1);

    void Render();

    bool IsDead();

    void Update(float dt);

    void NotifyCollision(GameObject &other, bool movements);

    bool Is(std::string className);

    void TakeDamage(float dmg = 1);

    float damage;

  private:
    Sprite sp;
    Timer timeElapsed;
    float duration;
    float attackDamage;
};

