#include "EvaDecker.h"
#include "Game.h"
#include "Config.h"
#include "Animation.h"
#include "AttackClass.h"

#define DECKER_ANIMATIONS 6
#define DECKER_ATTACKING 5
#define ATTACK_RENDER_OFFSET 60
#define DECKER_ATTACK_DAMAGE 4

EvaDecker::EvaDecker()
    : EvaClass(), atkTimer(), atkCooldown(), atkStarted(false), atkPos(0, 0),
      healthBar("sprites/hud/healthbar/DECKER/HUD-EVA-DECKER.png",
                "sprites/hud/healthbar/DECKER/HUD-EVA-DECKER-OVERLAY.png"),
      minimap("sprites/hud/minimap/HUD-EVA-DECKER-MINIMAP.png")
{
    std::string tFiles[DECKER_ANIMATIONS] = {
        "sprites/eva/movement/EVA-DECKER-IDLE.png",
        "sprites/eva/movement/EVA-DECKER-UP.png",
        "sprites/eva/movement/EVA-DECKER-LEFT.png",
        "sprites/eva/movement/EVA-DECKER-DOWN.png",
        "sprites/eva/movement/EVA-DECKER-RIGHT.png",
        "sprites/eva/attack/EVA-DECKER-ATTACK.png"};
    files = tFiles;
    frameCounts = new int[DECKER_ANIMATIONS]{6, 6, 6, 6, 6, 18};
    frameTimes =
            new float[DECKER_ANIMATIONS]{0.08, 0.08, 0.08, 0.08, 0.08, 0.08};
    int spriteRows[DECKER_ANIMATIONS]{1, 1, 1, 1, 1, 3};
    for (int i = 0; i < DECKER_ANIMATIONS; i++)
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i], spriteRows[i]);

    movSpeed = 200;
    atk = 1;
    def = 1;
    atkSpeed = 0.3;
    isAttacking = false;
    atkReady = true;
}

void EvaDecker::Update(float dt, float hp)
{
    animations.Update(dt);
    healthBar.Update(hp);

    if (isAttacking) {
        if (animations.GetCurrentFrame() == 13 && atkStarted)
            Shockwave(atkPos);
        if (animations.GetCurrentFrame() ==  17) {
            isAttacking = false;
        }
    }
    if (!atkReady) {
        atkCooldown.Update(dt);
        if (atkCooldown.Get() >= 17 * frameTimes[DECKER_ATTACKING] / atkSpeed) {
            atkReady = true;
            atkCooldown.Restart();
        }
    }
}

void EvaDecker::Attack(Vec2 pos, int direction)
{
    UNUSED_VAR direction;

    SetCurrentState(DECKER_ATTACKING);
    isAttacking = true;
    atkReady = false;
    atkPos = pos;
    atkStarted = true;
}

void EvaDecker::Die(Vec2 pos)
{
    Game::GetInstance()->GetCurrentState().AddObject(new Animation(
                                                         pos, 0, "sprites/eva/death/EVA-DECKER-DEATH.png", 16, 0.08));
}

void EvaDecker::Render(float x, float y)
{
    if (animations.GetCurrentState() == DECKER_ATTACKING)
        animations.Render(x - ATTACK_RENDER_OFFSET, y - ATTACK_RENDER_OFFSET);
    else
        animations.Render(x, y);
    healthBar.Render();
    minimap.Render();
}

void EvaDecker::Shockwave(Vec2 pos)
{
    atkStarted = false;

    Vec2 offset(-70, -60);
    Vec2 hitboxOffset(0, 0);
    Vec2 hitboxDim(260, 260);

    Game::GetInstance()->GetCurrentState().AddObject(new AttackClass(
                                                         pos + offset,
                                                         hitboxOffset,
                                                         hitboxDim,
                                                         atk, "", 5, 0.08));
}

