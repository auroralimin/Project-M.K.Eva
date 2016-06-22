#pragma once

#include "AnimationFSM.h"
#include "Vec2.h"
#include <string>

class EvaClass
{
  public:
    EvaClass(int nAnimations);

    virtual ~EvaClass(void)
    {
    }

    virtual void Update(float dt, float hp) = 0;

    virtual void Attack(Vec2 pos, int direction) = 0;

    virtual void Die(Vec2 pos) = 0;

    virtual void Render(float x, float y);

    virtual void SetCurrentState(int state);

    virtual bool IsAttacking(void);

    virtual bool AttackReady(void);

    int movSpeed;
    int atk;
    int def;
    float atkSpeed;
    AnimationFSM animations;

  protected:
    int currentState;
    std::string *files;
    float *frameTimes;
    int *frameCounts;
    bool isAttacking;
    bool atkReady;
};

