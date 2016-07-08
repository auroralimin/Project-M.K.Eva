#include "Boss.h"
#include "Camera.h"
#include "Bullet.h"
#include "Config.h"

#define BOSS_ANIMATIONS_1 9
#define BOSS_ANIMATIONS_2 10
Boss::Boss(Vec2 pos)
{
    animations[0] = AnimationFSM();
    animations[1] = AnimationFSM();
    std::string files1[BOSS_ANIMATIONS_1] = {
        "sprites/boss/animations/phase1/BOSS-MOVE-UP.png",
        "sprites/boss/animations/phase1/BOSS-MOVE-LEFT.png",
        "sprites/boss/animations/phase1/BOSS-MOVE-DOWN.png",
        "sprites/boss/animations/phase1/BOSS-MOVE-RIGHT.png",
        "sprites/boss/animations/phase1/BOSS-ATTACK-UP.png",
        "sprites/boss/animations/phase1/BOSS-ATTACK-LEFT.png",
        "sprites/boss/animations/phase1/BOSS-ATTACK-DOWN.png",
        "sprites/boss/animations/phase1/BOSS-ATTACK-RIGHT.png",
        "sprites/boss/animations/phase1/BOSS-SUMMON-BALL.png"
    };
    int frameCounts1[BOSS_ANIMATIONS_1]{10, 10, 10, 10, 10, 10, 10, 10, 20};
    float frameTimes1[BOSS_ANIMATIONS_1]{0.08, 0.08, 0.08, 0.08, 0.08,
        0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < BOSS_ANIMATIONS_1; i++)
        animations[0].SetAnimation(i, files1[i], frameCounts1[i], frameTimes1[i]);

    std::string files2[BOSS_ANIMATIONS_2] = {
        "sprites/boss/animations/phase2/BOSS-MOVE-UP.png",
        "sprites/boss/animations/phase2/BOSS-MOVE-LEFT.png",
        "sprites/boss/animations/phase2/BOSS-MOVE-DOWN.png",
        "sprites/boss/animations/phase2/BOSS-MOVE-RIGHT.png",
        "sprites/boss/animations/phase2/BOSS-ATTACK-UP.png",
        "sprites/boss/animations/phase2/BOSS-ATTACK-LEFT.png",
        "sprites/boss/animations/phase2/BOSS-ATTACK-DOWN.png",
        "sprites/boss/animations/phase2/BOSS-ATTACK-RIGHT.png",
        "sprites/boss/animations/phase2/BOSS-TELEPORT.png",
        "sprites/boss/animations/phase2/BOSS-TELEPORT-BACKWARDS.png"
    };
    int frameCounts2[BOSS_ANIMATIONS_2]{10, 10, 10, 10, 15, 15, 20, 15, 20,
        20};
    float frameTimes2[BOSS_ANIMATIONS_2]{0.08, 0.08, 0.08, 0.08, 0.08, 0.08,
        0.08, 0.08, 0.08, 0.08};
    for (int i = 0; i < BOSS_ANIMATIONS_2; i++)
        animations[1].SetAnimation(i, files2[i], frameCounts2[i], frameTimes2[i]);

    box.pos = pos;
    box.dim = Vec2(128, 128);
    hitbox.pos = box.pos;
    hitbox.dim = box.dim;
    attackHitbox.pos = box.pos;
    attackHitbox.dim = box.dim;
    hp = 500;
    currentPhase = 0;
    currentState = 2;
    animations[currentPhase].SetCurrentState(currentState);

}

void Boss::Render()
{
    int attackColor[4] = COLOR_ATTACK_HITBOX;
    if (Config::ATTACK_HITBOX_MODE)
        attackHitbox.RenderFilledRect(attackColor);

    int color[4] = COLOR_HITBOX;
    if (Config::HITBOX_MODE)
        hitbox.RenderFilledRect(color);

    animations[currentPhase].Render(box.pos.x - Camera::pos.x,
                                    box.pos.y - Camera::pos.y);
    healthBar.Render();
}

bool Boss::IsDead()
{
    return (hp <= 0);
}

void Boss::Update(float dt)
{
    animations[currentPhase].Update(dt);
    healthBar.Update(hp);
}

void Boss::NotifyCollision(GameObject &other, bool movement)
{
    if (other.Is("Bullet") || other.Is("Attack")) {
        Bullet &bullet = (Bullet &)other;
        if (!bullet.targetsPlayer)
            TakeDamage(50);
    }
}

bool Boss::Is(std::string className)
{
    return (className == "Boss");
}

void Boss::TakeDamage(float dmg)
{
    hp -= dmg;
}
