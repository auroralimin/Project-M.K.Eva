#include "EvaGunslinger.h"
#include "Game.h"
#include "Animation.h"
#include "Bullet.h"
#include "Config.h"

#define GUN_ANIMATIONS 9

EvaGunslinger::EvaGunslinger() : EvaClass(GUN_ANIMATIONS),
    healthBar("sprites/hud/healthbar/GUN/HUD-EVA-GUN.png",
              "sprites/hud/healthbar/GUN/HUD-EVA-GUN-OVERLAY.png")
{
    std::string tFiles[GUN_ANIMATIONS] = {
        "sprites/eva/movement/EVA-GUN-IDLE.png",
        "sprites/eva/movement/EVA-GUN-UP.png",
        "sprites/eva/movement/EVA-GUN-LEFT.png",
        "sprites/eva/movement/EVA-GUN-DOWN.png",
        "sprites/eva/movement/EVA-GUN-RIGHT.png",
        "sprites/eva/movement/EVA-GUN-UP.png",
        "sprites/eva/movement/EVA-GUN-LEFT.png",
        "sprites/eva/movement/EVA-GUN-DOWN.png",
        "sprites/eva/movement/EVA-GUN-RIGHT.png"};
    files = tFiles;
    frameCounts = new int[GUN_ANIMATIONS]{6, 6, 6, 6, 6, 6, 6, 6, 6};
    frameTimes = new float[GUN_ANIMATIONS]{0.08, 0.08, 0.08, 0.08, 0.08,
                                           0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < GUN_ANIMATIONS; i++)
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);

    movSpeed = 300;
    atk = 1;
    def = 1;
    atkSpeed = 2;
    atkCooldown.Restart();
    atkTimer.Restart();
    isAttacking = false;
    atkReady = true;
}

void EvaGunslinger::Update(float dt, float hp)
{
    animations.Update(dt);
    healthBar.Update(hp);

    if (isAttacking) {
        atkTimer.Update(dt);
        if (atkTimer.Get() >=
            frameCounts[currentState] * frameTimes[currentState]) {
            isAttacking = false;
            atkTimer.Restart();
        }
    }
    if (!atkReady) {
        atkCooldown.Update(dt);
        if (atkCooldown.Get() >=
            frameCounts[currentState] * frameTimes[currentState] / atkSpeed) {
            atkReady = true;
            atkCooldown.Restart();
        }
    }
}

void EvaGunslinger::Attack(Vec2 pos, int direction)
{
    if (direction >= Config::directions::UP &&
        direction <= Config::directions::RIGHT) {
        SetCurrentState(direction + 5);
        isAttacking = true;
        atkReady = false;

        Vec2 offsets[4] = {{62, 0}, {10, 28}, {62, 46}, {110, 28}};
        Game::GetInstance()->GetCurrentState().AddObject(new Bullet(
            pos + offsets[direction], 3 * (M_PI / 2) - (M_PI / 2) * direction,
            500, 400, "sprites/eva/attack/GUN-SPELLEFFECT.png", Vec2(-10, -10),
            Vec2(20, 20), 4, 0.08f));
    }
}

void EvaGunslinger::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(
                new Animation(pos, 0, "sprites/eva/death/EVA-GUN-DEATH.png", 16, 0.08));
}

void EvaGunslinger::Render(float x, float y)
{
    animations.Render(x, y);
    healthBar.Render();
}

