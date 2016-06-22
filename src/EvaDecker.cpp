#include "EvaDecker.h"
#include "Game.h"
#include "Config.h"
#include "Animation.h"
#include "AttackClass.h"

#define DECKER_ANIMATIONS 6
#define DECKER_ATTACKING 5

EvaDecker::EvaDecker() : EvaClass(DECKER_ANIMATIONS),
    atkTimer(), atkCooldown(), atkStarted(false), atkPos(0, 0)
{
    std::string tFiles[DECKER_ANIMATIONS] = {
        "sprites/eva/movement/EVA-DECKER-IDLE.png",
        "sprites/eva/movement/EVA-DECKER-UP.png",
        "sprites/eva/movement/EVA-DECKER-LEFT.png",
        "sprites/eva/movement/EVA-DECKER-DOWN.png",
        "sprites/eva/movement/EVA-DECKER-RIGHT.png",
        "sprites/eva/movement/EVA-DECKER-DOWN.png"};
    files = tFiles;
    frameCounts = new int[DECKER_ANIMATIONS] {6, 6, 6, 6, 6, 6};
    frameTimes = new float[DECKER_ANIMATIONS] {0.08, 0.08, 0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < DECKER_ANIMATIONS; i++)
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);

    movSpeed = 200;
    atk = 1;
    def = 1;
    atkSpeed = 0.3;
    isAttacking = false;
    atkReady = true;
}

void EvaDecker::Update(float dt)
{
    animations.Update(dt);

    //hardcoded numbers will be changed with final sprite
    if (isAttacking) {
        atkTimer.Update(dt);
        if (atkTimer.Get() >= 13*frameTimes[DECKER_ATTACKING] && atkStarted)
            Shockwave(atkPos);
        if (atkTimer.Get() >= 18*frameTimes[DECKER_ATTACKING]){
            isAttacking = false;
            atkTimer.Restart();
        }
    }
    if (!atkReady) {
        atkCooldown.Update(dt);
        if (atkCooldown.Get() >= 18*frameTimes[DECKER_ATTACKING]/atkSpeed) {
            atkReady = true;
            atkCooldown.Restart();
        }
    }
}

void EvaDecker::Attack(Vec2 pos, int direction)
{
    UNUSED_VAR direction;

    SetCurrentState(DECKER_ATTACKING);
    isAttacking = true;
    atkReady = false;
    atkPos = pos;
    atkStarted = true;
}

void EvaDecker::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(
            new Animation(pos, 0,
                "sprites/eva/death/EVA-DECKER-DEATH.png", 16, 0.08));
}

void EvaDecker::Shockwave(Vec2 pos)
{
    atkStarted = false;

    int signalsX[4] = {1, -1, -1,  1};
    int signalsY[4] = {1,  1, -1, -1};
    for (int i = 0; i < 4; ++i)
        Game::GetInstance()->GetCurrentState().AddObject(
                new AttackClass(pos + Vec2(60*signalsX[i], 60*signalsY[i]),
                    Vec2(0, 0), Vec2(130, 130),
                    0, "sprites/eva/attack/aliendeath.png", 4, 0.08f));
}

