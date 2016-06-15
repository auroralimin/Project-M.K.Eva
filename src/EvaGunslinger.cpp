#include "EvaGunslinger.h"
#include "Game.h"
#include "Animation.h"

EvaGunslinger::EvaGunslinger() : EvaClass(5)
{
    std::string tFiles[5] = { std::string("sprites/eva/movement/EVA-GUN-IDLE.png"),
              std::string("sprites/eva/movement/EVA-GUN-UP.png"),
              std::string("sprites/eva/movement/EVA-GUN-DOWN.png"),
              std::string("sprites/eva/movement/EVA-GUN-LEFT.png"),
              std::string("sprites/eva/movement/EVA-GUN-RIGHT.png"),
            };
    files = tFiles;
    frameCounts = new int[5] {6, 6, 6, 6, 6};
    frameTimes = new float[5] {0.08, 0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < 5; i++) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }
    movSpeed = 200;
    atk = 1;
    def = 1;
    atkSpeed = 1;
}

void EvaGunslinger::Update(float dt)
{
    animations.Update(dt);
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
    //TODO
}

void EvaGunslinger::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(
                new Animation(pos, 0,
                              std::string(
                                  "sprites/eva/death/EVA-GUN-DEATH.png"),
                              16, 0.08));
}
