#include "EvaSamurai.h"
#include "Game.h"
#include "Animation.h"

EvaSamurai::EvaSamurai() : EvaClass(9)
{
    std::string tFiles[9] = { std::string("sprites/eva/movement/EVA-SAMURAI-IDLE.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-UP.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-DOWN.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-LEFT.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-RIGHT.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-UP.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-DOWN.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-LEFT.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-RIGHT.png")
            };
    files = tFiles;
    frameCounts = new int[9] {6, 6, 6, 6, 6, 6, 6, 6, 6};
    frameTimes = new float[9] {0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < 9; i++) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }
    movSpeed = 200;
    atk = 1;
    def = 99;
    atkSpeed = 0.9;
    isAttacking = false;
    atkReady = true;
}

void EvaSamurai::Update(float dt)
{
    animations.Update(dt);
    if (isAttacking) {
        atkTimer.Update(dt);
        if (atkTimer.Get() >= frameCounts[currentState]*frameTimes[currentState]) {
            isAttacking = false;
            atkTimer.Restart();
        }
    }
    if (!atkReady) {
        atkCooldown.Update(dt);
        if (atkCooldown.Get() >= frameCounts[currentState]*frameTimes[currentState]/atkSpeed) {
            atkReady = true;
            atkCooldown.Restart();
        }
    }
}

void EvaSamurai::Render(float x, float y)
{
    animations.Render(x, y);
}

void EvaSamurai::SetCurrentState(int state)
{
    currentState = state;
    animations.SetCurrentState(state);
}

void EvaSamurai::Attack(int direction)
{
    if (direction > 4 && direction < 9) {
        SetCurrentState(direction);
        isAttacking = true;
    }
}

void EvaSamurai::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(
                new Animation(pos, 0,
                              std::string(
                                  "sprites/eva/death/EVA-SAMURAI-DEATH.png"),
                              16, 0.08));
}

bool EvaSamurai::IsAttacking()
{
    return isAttacking;
}

bool EvaSamurai::AttackReady()
{
    return atkReady;
}
