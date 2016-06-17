#include "EvaGunslinger.h"
#include "Game.h"
#include "Animation.h"
#include "Bullet.h"
#include "Config.h"

#define GUN_ANIMATIONS 9

EvaGunslinger::EvaGunslinger() : EvaClass(GUN_ANIMATIONS)
{
    std::string tFiles[GUN_ANIMATIONS] = { std::string("sprites/eva/movement/EVA-GUN-IDLE.png"),
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
    frameCounts = new int[GUN_ANIMATIONS] {6, 6, 6, 6, 6, 6, 6, 6, 6};
    frameTimes = new float[GUN_ANIMATIONS] {0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < GUN_ANIMATIONS; i++) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }
    movSpeed = 300;
    atk = 1;
    def = 1;
    atkSpeed = 2;
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
        if (atkCooldown.Get() >= frameCounts[currentState]*frameTimes[currentState]/atkSpeed) {
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

void EvaGunslinger::Attack(Vec2 pos, int direction)
{
    if (direction > UP - 1 && direction < RIGHT + 1) {
        SetCurrentState(direction);
        isAttacking = true;
        atkReady = false;
        float range = 400;
        Vec2 offsetUp(95, 0);
        Vec2 offsetDown(110, 0);
        Vec2 offsetHorizontal(120, 0);
        switch (direction) {
        case UP:
            Game::GetInstance()->GetCurrentState().AddObject(
                        new Bullet(pos + offsetUp, -M_PI/2, 500, range,
                                   std::string(
                                       "sprites/eva/attack/GUN-SPELLEFFECT.png"),
                                   4, 0.08f));
            break;
        case DOWN:
            Game::GetInstance()->GetCurrentState().AddObject(
                        new Bullet(pos + offsetDown, M_PI/2, 500, range,
                                   std::string(
                                       "sprites/eva/attack/GUN-SPELLEFFECT.png"),
                                   4, 0.08f));
            break;
        case LEFT:
            Game::GetInstance()->GetCurrentState().AddObject(
                        new Bullet(pos + offsetHorizontal, M_PI, 500, range,
                                   std::string(
                                       "sprites/eva/attack/GUN-SPELLEFFECT-2.png"),
                                   4, 0.08f));
            break;
        case RIGHT:
            Game::GetInstance()->GetCurrentState().AddObject(
                        new Bullet(pos + offsetHorizontal, 0, 500, range,
                                   std::string(
                                       "sprites/eva/attack/GUN-SPELLEFFECT-2.png"),
                                   4, 0.08f));
            break;
        default:
            break;
        }
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
