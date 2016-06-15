#include "EvaDecker.h"
#include "Game.h"
#include "Animation.h"

EvaDecker::EvaDecker() : EvaClass(5)
{
    std::string tFiles[5] = { std::string("sprites/eva/movement/EVA-DECKER-IDLE.png"),
              std::string("sprites/eva/movement/EVA-DECKER-UP.png"),
              std::string("sprites/eva/movement/EVA-DECKER-DOWN.png"),
              std::string("sprites/eva/movement/EVA-DECKER-LEFT.png"),
              std::string("sprites/eva/movement/EVA-DECKER-RIGHT.png"),
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

void EvaDecker::Update(float dt)
{
    animations.Update(dt);
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

void EvaDecker::Attack(int direction)
{
    //TODO
}

void EvaDecker::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(
                new Animation(pos, 0,
                              std::string(
                                  "sprites/eva/death/EVA-DECKER-DEATH.png"),
                              16, 0.08));
}
