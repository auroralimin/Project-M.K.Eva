#include "EvaSamurai.h"
#include "Game.h"
#include "Animation.h"
#include "Bullet.h"
#include "AttackClass.h"
#include "Config.h"

#define SAMURAI_ANIMATIONS 9
#define SAMURAI_ATTACK_DAMAGE 5.6

#define MINIMAP_X 900
#define MINIMAP_Y 5

EvaSamurai::EvaSamurai() : EvaClass(),
  healthBar("sprites/hud/healthbar/SAMURAI/HUD-EVA-SAMURAI.png",
            "sprites/hud/healthbar/SAMURAI/HUD-EVA-SAMURAI-OVERLAY.png"),
  minimap("sprites/hud/minimap/HUD-EVA-SAMURAI-MINIMAP.png")

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
        0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f, 0.12f};
    for (int i = 0; i < SAMURAI_ANIMATIONS; i++)
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);

    movSpeed = 175;
    atk = 10;
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

        std::string sprites[4] = {
            "sprites/eva/attack/EVA-SAMURAI-ATTACK-UP-SpellEffect.png",
            "sprites/eva/attack/EVA-SAMURAI-ATTACK-LEFT-SpellEffect.png",
            "sprites/eva/attack/EVA-SAMURAI-ATTACK-DOWN-SpellEffect.png",
            "sprites/eva/attack/EVA-SAMURAI-ATTACK-RIGHT-SpellEffect.png"};

        Vec2 offsets[4] = {{0, -60}, {-60, 0}, {0, 0}, {0, 0}};
        Vec2 hitboxOffsets[4] = {{0, 0}, {0, 0}, {0, 40}, {35, 0}};
        Vec2 hitboxDim[4] = {{120, 160}, {150, 120}, {120, 140}, {150, 120}};
        Game::GetInstance()->GetCurrentState().AddObject(new AttackClass(
            pos + offsets[direction], hitboxOffsets[direction],
            hitboxDim[direction], atk, sprites[direction], 4, 0.08f));
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
    minimap.Render(MINIMAP_X, MINIMAP_Y);
}

