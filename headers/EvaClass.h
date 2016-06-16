#pragma once

#include "AnimationFSM.h"
#include "Vec2.h"
#include <string>

class EvaClass
{
public:
    EvaClass(int nAnimations);

    virtual ~EvaClass() {}

    virtual void Update(float dt) = 0;

    virtual void Render(float x, float y) = 0;

    virtual void SetCurrentState(int state) = 0;

    virtual void Attack(Vec2 pos, int direction) = 0;

    virtual void Die(Vec2 pos) = 0;

    virtual bool IsAttacking() = 0;

    virtual bool AttackReady() = 0;

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
