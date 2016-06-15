#include "EvaSamurai.h"
#include "Game.h"
#include "Animation.h"

EvaSamurai::EvaSamurai() : EvaClass(5)
{
    std::string tFiles[5] = { std::string("sprites/eva/movement/EVA-SAMURAI-IDLE.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-UP.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-DOWN.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-LEFT.png"),
              std::string("sprites/eva/movement/EVA-SAMURAI-RIGHT.png"),
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

void EvaSamurai::Update(float dt)
{
    animations.Update(dt);
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
    //TODO
}

void EvaSamurai::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(
                new Animation(pos, 0,
                              std::string(
                                  "sprites/eva/death/EVA-SAMURAI-DEATH.png"),
                              16, 0.08));
}
