#include "BallsManager.h"
#include "Game.h"
#include "Config.h"
#include "Eva.h"
#include "Collision.h"
#include "Animation.h"

#define ARENA_WIDTH_INIT 128
#define ARENA_WIDTH_END 1152
#define ARENA_HEIGHT_INIT 256
#define ARENA_HEIGHT_END 576
#define REST_TIME 3.6
#define WARN_TIME 2.0
#define ATTACK_TIME 1.8
#define BALL_EVA_DISTANCE 50

BallsManager::BallsManager(Room *room, GameObject *focus)
    : room(room), focus(focus), currentState(BallsState::RESTING)
{
    attackHitbox.dim = Vec2(0, 0);
}

BallMonster **BallsManager::AddBall(void)
{
    float x = Config::Rand(ARENA_WIDTH_INIT, ARENA_WIDTH_END);
    float y = Config::Rand(ARENA_HEIGHT_INIT, ARENA_HEIGHT_END);
    ballArray.emplace_back(new BallMonster(room, Vec2(x - 43, y - 110)));
    return &ballArray[ballArray.size() - 1];
}

void BallsManager::Render()
{

}

bool BallsManager::IsDead()
{
    return ballArray.empty();
}

void BallsManager::Update(float dt)
{
    timer.Update(dt);

    if (focus != nullptr) {
        attackHitbox.pos.x = focus->box.pos.x - 45;
        attackHitbox.pos.y = focus->box.pos.y - 70;
        attackHitbox.dim = Vec2(0, 0);
        if (currentState == BallsState::RESTING && timer.Get() >= REST_TIME) {
            currentState = BallsState::WARNING;
            timer.Restart();
            SetCurrentState(WARNING);
        } else if (currentState == BallsState::WARNING &&
                   timer.Get() >= WARN_TIME) {
            currentState = BallsState::ATTACKING;
            timer.Restart();
            SetCurrentState(ATTACKING);
            for (size_t i = 0; (i < ballArray.size()) && (focus != nullptr); i++) {
                Game::GetInstance()->GetCurrentState().AddObject(new Animation(
                        ballArray[i]->box.pos, 0, "sprites/monsters/ball/BOLOTA_BLINK.png", 6,
                        0.02, true));
            }

        } else if (currentState == BallsState::ATTACKING) {
            attackHitbox.dim = Vec2(220, 180);
            for (size_t i = 0; (i < ballArray.size()) && (focus != nullptr); i++) {
                float angle = 2 * M_PI * (i + 1) / ballArray.size();
                Vec2 pos = Vec2(BALL_EVA_DISTANCE, 60);
                ballArray[i]->box.pos =
                    Vec2(pos.x * cos(angle) - pos.y * sin(angle),
                         pos.y * cos(angle) + pos.x * sin(angle));

                Vec2 evaPos = focus->box.pos + Vec2(0, 70);
                evaPos.y -= focus->box.dim.y / 2;
                ballArray[i]->box.pos += evaPos;

                focus->TakeDamage(ballArray.size() * 1.5);
            }
            if (timer.Get() >= ATTACK_TIME) {
                currentState = BallsState::RESTING;
                RandTeleport();
                timer.Restart();
                SetCurrentState(RESTING);
            }
        }
    } else {
        currentState = BallsState::RESTING;
        SetCurrentState(RESTING);
    }
        
    ClearDeadBalls();
}

void BallsManager::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR other;
    UNUSED_VAR movement;
}

bool BallsManager::Is(std::string className)
{
    return (className == std::string("BallsManager"));
}

void BallsManager::TakeDamage(float dmg)
{
    UNUSED_VAR dmg;
}

void BallsManager::SetCurrentState(int currentState)
{
    for (size_t i = 0; i < ballArray.size(); i++) {
        ballArray[i]->SetCurrentState(currentState);
    }
}

void BallsManager::RandTeleport()
{
    Rect box;
    for (size_t i = 0; i < ballArray.size(); i++) {
        do {
            box = ballArray[i]->box;
            float x = Config::Rand(85, 1109);
            float y = Config::Rand(146, 466);
            box.pos = Vec2(x, y);
        } while (Collision::IsColliding(box, focus->box, 0, 0));

        ballArray[i]->box.pos = box.pos;
        ballArray[i]->attackHitbox.pos = Vec2(box.pos.x + 43, box.pos.y + 110);
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            ballArray[i]->box.pos, 0, "sprites/monsters/ball/BOLOTA_BLINK.png", 6,
            0.02, true));
    }
}

void BallsManager::ClearDeadBalls()
{
    for (unsigned int i = 0; i < ballArray.size(); i ++) {
        if (ballArray[i]->IsDead()) {
            ballArray.erase(ballArray.begin() + i);
        }
    }
}

