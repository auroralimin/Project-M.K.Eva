#include "EvaDecker.h"
#include "Game.h"
#include "Animation.h"
#include "AttackClass.h"

EvaDecker::EvaDecker() : EvaClass(6)
{
    std::string tFiles[6] = { std::string("sprites/eva/movement/EVA-DECKER-IDLE.png"),
              std::string("sprites/eva/movement/EVA-DECKER-UP.png"),
              std::string("sprites/eva/movement/EVA-DECKER-DOWN.png"),
              std::string("sprites/eva/movement/EVA-DECKER-LEFT.png"),
              std::string("sprites/eva/movement/EVA-DECKER-RIGHT.png"),
              std::string("sprites/eva/movement/EVA-DECKER-DOWN.png"),
            };
    files = tFiles;
    frameCounts = new int[6] {6, 6, 6, 6, 6, 6};
    frameTimes = new float[6] {0.08, 0.08, 0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < 6; i++) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }
    movSpeed = 200;
    atk = 1;
    def = 1;
    atkSpeed = 0.3;
    atkTimer.Restart();
    atkCooldown.Restart();
    isAttacking = false;
    atkReady = true;
    atkStarted = false;
}

void EvaDecker::Update(float dt)
{
    animations.Update(dt);
    if (isAttacking) {
        atkTimer.Update(dt);
        if (atkTimer.Get() >= 13*frameTimes[5] && atkStarted)
            Shockwave(atkPos);
        if (atkTimer.Get() >= 18*frameTimes[5]){
            isAttacking = false;
            atkTimer.Restart();
        }
    }
    if (!atkReady) {
        atkCooldown.Update(dt);
        if (atkCooldown.Get() >= 18*frameTimes[5]/atkSpeed) {
            atkReady = true;
            atkCooldown.Restart();
        }
    }
}

void EvaDecker::Render(float x, float y)
{
    animations.Render(x, y);
}

void EvaDecker::SetCurrentState(int state)
{
    currentState = state;
    animations.SetCurrentState(state);
}

void EvaDecker::Attack(Vec2 pos, int direction)
{
    SetCurrentState(5);
    isAttacking = true;
    atkReady = false;
    atkPos = pos;
    atkStarted = true;
}

void EvaDecker::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(
                new Animation(pos, 0,
                              std::string(
                                  "sprites/eva/death/EVA-DECKER-DEATH.png"),
                              16, 0.08));
}

bool EvaDecker::IsAttacking()
{
    return isAttacking;
}

bool EvaDecker::AttackReady()
{
    return atkReady;
}

void EvaDecker::Shockwave(Vec2 pos)
{
    atkStarted = false;
    Game::GetInstance()->GetCurrentState().AddObject(
                new AttackClass(pos + Vec2(60, 60), 0,
                           std::string(
                               "sprites/eva/attack/aliendeath.png"),
                           4, 0.08f));

    Game::GetInstance()->GetCurrentState().AddObject(
                new AttackClass(pos + Vec2(-60, 60), 0,
                           std::string(
                               "sprites/eva/attack/aliendeath.png"),
                           4, 0.08f));

    Game::GetInstance()->GetCurrentState().AddObject(
                new AttackClass(pos + Vec2(-60, -60), 0,
                           std::string(
                               "sprites/eva/attack/aliendeath.png"),
                           4, 0.08f));

    Game::GetInstance()->GetCurrentState().AddObject(
                new AttackClass(pos + Vec2(60, -60), 0,
                           std::string(
                               "sprites/eva/attack/aliendeath.png"),
                           4, 0.08f));
}
