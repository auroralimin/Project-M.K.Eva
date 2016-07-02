#include "MekaBug.h"
#include "Eva.h"
#include "Config.h"
#include "Game.h"
#include "InputManager.h"
#include "Animation.h"
#include "Bullet.h"
#include "Collision.h"

#define MEKABUG_ANIMATIONS 2

MekaBug::MekaBug(Vec2 pos, GameObject *focus)
    : focus(focus), animations(MEKABUG_ANIMATIONS),
      movState(MekaBugMovement::RESTING), previousPos(pos), stuck(false)
{
    std::string files[MEKABUG_ANIMATIONS] = {
        "sprites/monsters/mekabug/MEKABUG_SPRITESHEET.png",
        "sprites/monsters/mekabug/MEKABUG_ATTACK_SPRITESHEET.png"};
    int frameCounts[MEKABUG_ANIMATIONS] = {6, 5};
    float frameTimes[MEKABUG_ANIMATIONS] = {0.3, 0.3};
    for (int i = 0; i < MEKABUG_ANIMATIONS; i++) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }

    box.pos = pos;
    box.dim = Vec2(animations.GetCurrentWidth(), animations.GetCurrentHeight());
    hitbox.dim = Vec2(box.dim.x, box.dim.y / 2);
    hitbox.pos = Vec2(box.pos.x, box.pos.y + 35);
    attackHitbox.dim = Vec2(box.dim.x, box.dim.y/1.5);
    attackHitbox.pos = Vec2(box.pos.x, box.pos.y + box.dim.y/1.5);

    hp = 100;
    rotation = 0;
}

void MekaBug::Render()
{
    animations.Render(box.pos.x, box.pos.y);

    int attackColor[4] = COLOR_ATTACK_HITBOX;
    if (Config::ATTACK_HITBOX_MODE)
        attackHitbox.RenderFilledRect(attackColor);
}

bool MekaBug::IsDead()
{
    return (hp <= 0);
}

void MekaBug::Update(float dt)
{
    // temporary suicide button
    if (InputManager::GetInstance().KeyPress(J_KEY))
        TakeDamage(8000);

    MovementAndAttack(dt);
    animations.Update(dt);
}

void MekaBug::NotifyCollision(GameObject &other, bool movement)
{
    if (other.Is("Bullet") || other.Is("Attack")) {
        Bullet &bullet = (Bullet &)other;
        if (!bullet.targetsPlayer)
            TakeDamage(10);
    } else if (movement && (!other.Is("Ball"))) {
        box.pos = previousPos;
        if (other.Is("MekaBug"))
            stuck = true;
    }
}

bool MekaBug::Is(std::string className)
{
    return ("MekaBug" == className);
}

void MekaBug::TakeDamage(float dmg)
{
    hp -= dmg;
    if (IsDead())
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            box.GetCenter(), 0, "sprites/monsters/mekabug/MEKABUG_DEATH.png", 3,
            0.5, true));
}

void MekaBug::MovementAndAttack(float dt)
{
    static Timer restTimer = Timer(), stuckTimer = Timer();
    Vec2 speed = Vec2(0, 0);

    if (movState == MekaBugMovement::RESTING) {
        restTimer.Update(dt);

        if (restTimer.Get() >= Config::Rand(10, 25) / 10.0f) {
            movState = MekaBugMovement::MOVING;
            animations.SetCurrentState(MekaBugState::PASSIVE);
        }
    } else if (movState == MekaBugMovement::MOVING) {
        Vec2 evaPos = focus->box.GetCenter();
        if (Collision::IsColliding(focus->hitbox, hitbox, focus->rotation,
                                   rotation)) {
            movState = MekaBugMovement::RESTING;
            animations.SetCurrentState(MekaBugState::AGRESSIVE);
            restTimer.Restart();
        } else {
            speed = (evaPos - box.pos).Norm() * 100 * dt;
            previousPos = box.pos;
            if (stuck) {
                stuckTimer.Update(dt);
                float angle = (Config::Rand(90, 180) * M_PI) / 180.0f;
                box.pos += speed.Rotate(angle);
                if (stuckTimer.Get() >= 0.5) {
                    stuck = false;
                    stuckTimer.Restart();
                }
            } else {
                box.pos += speed;
            }
        }

        if (Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this)) {
            box.pos = previousPos;
            movState = MekaBugMovement::RESTING;
            restTimer.Restart();
        }
    }

    hitbox.pos = Vec2(box.pos.x, box.pos.y + 35);
    attackHitbox.pos = Vec2(box.pos.x, box.pos.y + box.dim.y/3);
}

