#pragma once

#include "GameObject.h"
#include "AnimationFSM.h"
#include "BossHealthBar.h"

class Boss : public GameObject
{
public:
    Boss(Vec2 pos);

    void Render();
    bool IsDead();
    void Update(float dt);
    void NotifyCollision(GameObject &other, bool movement);
    bool Is(std::string className);
    void TakeDamage(float dmg = 1);

private:
    AnimationFSM animations[2];
    BossHealthBar healthBar;
    int currentPhase;
    int currentState;

};
