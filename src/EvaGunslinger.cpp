#include "EvaGunslinger.h"
#include "Game.h"
#include "Animation.h"

EvaGunslinger::EvaGunslinger() : EvaClass(9)
{
    std::string tFiles[9] = { std::string("sprites/eva/movement/EVA-GUN-IDLE.png"),
              std::string("sprites/eva/movement/EVA-GUN-UP.png"),
              std::string("sprites/eva/movement/EVA-GUN-DOWN.png"),
              std::string("sprites/eva/movement/EVA-GUN-LEFT.png"),
              std::string("sprites/eva/movement/EVA-GUN-RIGHT.png"),
              std::string("sprites/eva/movement/EVA-GUN-UP.png"),
              std::string("sprites/eva/movement/EVA-GUN-DOWN.png"),
              std::string("sprites/eva/movement/EVA-GUN-LEFT.png"),
              std::string("sprites/eva/movement/EVA-GUN-RIGHT.png")
            };
    files = tFiles;
    frameCounts = new int[9] {6, 6, 6, 6, 6, 6, 6, 6, 6};
    frameTimes = new float[9] {0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < 9; i++) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }
    movSpeed = 300;
    atk = 1;
    def = 1;
    atkSpeed = 1;
    atkCooldown.Restart();
    atkTimer.Restart();
    isAttacking = false;
    atkReady = true;
}

void EvaGunslinger::Update(float dt)
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
        if (atkCooldown.Get() >= atkSpeed) {
            atkReady = true;
            atkCooldown.Restart();
        }
    }
}

void EvaGunslinger::Render(float x, float y)
{
    animations.Render(x, y);
}

void EvaGunslinger::SetCurrentState(int state)
{
    currentState = state;
    animations.SetCurrentState(state);
}

void EvaGunslinger::Attack(int direction)
{
    if (direction > 4 && direction < 9) {
        SetCurrentState(direction);
        isAttacking = true;
    }
}

void EvaGunslinger::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(
                new Animation(pos, 0,
                              std::string(
                                  "sprites/eva/death/EVA-GUN-DEATH.png"),
                              16, 0.08));
}

bool EvaGunslinger::IsAttacking()
{
    return isAttacking;
}

bool EvaGunslinger::AttackReady()
{
    return atkReady;
}
