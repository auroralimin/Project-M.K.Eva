#include "MonsterBallManager.h"
#include "Game.h"
#include "Config.h"
#include "Eva.h"

#define ARENA_WIDTH_INIT 128
#define ARENA_WIDTH_END 1152
#define ARENA_HEIGHT_INIT 256
#define ARENA_HEIGHT_END 576
#define REST_TIME 5.8
#define WARN_TIME 3.2
#define ATTACK_TIME 5.0
#define BALL_EVA_DISTANCE 50

MonsterBallManager::MonsterBallManager(GameObject *focus)
    : focus(focus), currentState(BallsState::RESTING)
{
    hitbox.dim = Vec2(0, 0);
}

Ball **MonsterBallManager::AddBall(void)
{
    float x = Config::Rand(ARENA_WIDTH_INIT, ARENA_WIDTH_END);
    float y = Config::Rand(ARENA_HEIGHT_INIT, ARENA_HEIGHT_END);
    ballArray.emplace_back(new Ball(Vec2(x - 43, y - 110)));
    return &ballArray[ballArray.size() - 1];
}

void MonsterBallManager::Render()
{
    int color[4] = COLOR_HITBOX;
    if (Config::HITBOX_MODE)
        hitbox.RenderFilledRect(color);
}

bool MonsterBallManager::IsDead()
{
    return ballArray.empty();
}

void MonsterBallManager::Update(float dt)
{
    timer.Update(dt);

    hitbox.pos.x = focus->box.pos.x - 45;
    hitbox.pos.y = focus->box.pos.y - 70;
    hitbox.dim = Vec2(0, 0);
    if (currentState == BallsState::RESTING && timer.Get() >= REST_TIME) {
        currentState = BallsState::WARNING;
        timer.Restart();
        SetCurrentState(WARNING);
    } else if (currentState == BallsState::WARNING &&
               timer.Get() >= WARN_TIME) {
        currentState = BallsState::ATTACKING;
        timer.Restart();
        SetCurrentState(ATTACKING);
    } else if (currentState == BallsState::ATTACKING) {
        hitbox.dim = Vec2(220, 180);
        for (size_t i = 0; i < ballArray.size(); i++) {
            float angle = 2 * M_PI * (i + 1) / ballArray.size();
            Vec2 pos = Vec2(BALL_EVA_DISTANCE, 0);
            ballArray[i]->box.pos =
                Vec2(pos.x * cos(angle) - pos.y * sin(angle),
                     pos.y * cos(angle) + pos.x * sin(angle));

            Vec2 evaPos = focus->box.pos;
            evaPos.y -= focus->box.dim.y / 2;
            ballArray[i]->box.pos += evaPos;
        }

        if (timer.Get() >= ATTACK_TIME) {
            currentState = BallsState::RESTING;
            RandTeleport();
            timer.Restart();
            SetCurrentState(RESTING);
        }
    }
}

void MonsterBallManager::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR other;
    UNUSED_VAR movement;
}

bool MonsterBallManager::Is(std::string className)
{
    return (className == std::string("MonsterBallManager"));
}

void MonsterBallManager::TakeDamage(float dmg)
{
    UNUSED_VAR dmg;
}

void MonsterBallManager::SetCurrentState(int currentState)
{
    for (size_t i = 0; i < ballArray.size(); i++) {
        ballArray[i]->SetCurrentState(currentState);
    }
}

void MonsterBallManager::RandTeleport()
{
    for (size_t i = 0; i < ballArray.size(); i++) {
        float x = Config::Rand(85, 1109);
        float y = Config::Rand(146, 466);
        ballArray[i]->box.pos = Vec2(x, y);
        ballArray[i]->hitbox.pos = Vec2(box.pos.x + 43, box.pos.y + 110);
    }
}

