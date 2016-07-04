#include "EvaSamurai.h"
#include "Game.h"
#include "Animation.h"
#include "Bullet.h"
#include "AttackClass.h"
#include "Config.h"

#define SAMURAI_ANIMATIONS 9
EvaSamurai::EvaSamurai() : EvaClass(SAMURAI_ANIMATIONS),
  healthBar("sprites/hud/healthbar/SAMURAI/HUD-EVA-SAMURAI.png",
            "sprites/hud/healthbar/SAMURAI/HUD-EVA-SAMURAI-OVERLAY.png")
{
    std::string tFiles[SAMURAI_ANIMATIONS] = {
        "sprites/eva/movement/EVA-SAMURAI-IDLE.png",
        "sprites/eva/movement/EVA-SAMURAI-UP.png",
        "sprites/eva/movement/EVA-SAMURAI-LEFT.png",
        "sprites/eva/movement/EVA-SAMURAI-DOWN.png",
        "sprites/eva/movement/EVA-SAMURAI-RIGHT.png",
        "sprites/eva/attack/EVA-SAMURAI-ATTACK-UP.png",
        "sprites/eva/attack/EVA-SAMURAI-ATTACK-LEFT.png",
        "sprites/eva/attack/EVA-SAMURAI-ATTACK-DOWN.png",
        "sprites/eva/attack/EVA-SAMURAI-ATTACK-RIGHT.png"};
    files = tFiles;
    frameCounts = new int[SAMURAI_ANIMATIONS]{6, 6, 6, 6, 6, 4, 4, 4, 4};
    frameTimes = new float[SAMURAI_ANIMATIONS]{
        0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f, 0.08f};
    for (int i = 0; i < SAMURAI_ANIMATIONS; i++)
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);

    movSpeed = 100;
    atk = 1;
    def = 40;
    atkSpeed = 0.8;
    isAttacking = false;
    atkReady = true;
}

void EvaSamurai::Update(float dt, float hp)
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

void EvaSamurai::Attack(Vec2 pos, int direction)
{
    if (direction >= Config::directions::UP &&
        direction <= Config::directions::RIGHT) {
        SetCurrentState(direction + 5);
        isAttacking = true;
        atkReady = false;
        //fix this. this is wrong in so many ways
        std::string sprites[4] = {
            "sprites/eva/attack/EVA-SAMURAI-ATTACK-UP-SpellEffect.png",
            "sprites/eva/attack/EVA-SAMURAI-ATTACK-LEFT-SpellEffect.png",
            "sprites/eva/attack/EVA-SAMURAI-ATTACK-DOWN-SpellEffect.png",
            "sprites/eva/attack/EVA-SAMURAI-ATTACK-RIGHT-SpellEffect.png"};

        Vec2 offsets[4] = {{20, -25}, {-85, 20}, {10, 100}, {-35, 20}};
        Vec2 hitboxOffsets[4] = {{10, 5}, {80, -70}, {5, -30}, {85, -70}};
        Vec2 hitboxDim[4] = {{75, 100}, {75, 150}, {75, 100}, {75, 150}};
        Game::GetInstance()->GetCurrentState().AddObject(new AttackClass(
            pos + offsets[direction], hitboxOffsets[direction],
            hitboxDim[direction], 4, sprites[direction], 4, 0.08f));
    }
}

void EvaSamurai::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(new Animation(
                                                         pos, 0, "sprites/eva/death/EVA-SAMURAI-DEATH.png", 16, 0.08));
}

void EvaSamurai::Render(float x, float y)
{
    animations.Render(x, y);
    healthBar.Render();
}

