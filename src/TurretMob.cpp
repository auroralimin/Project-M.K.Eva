#include <math.h>

#include "TurretMob.h"
#include "Eva.h"
#include "Bullet.h"
#include "Game.h"
#include "Config.h"
#include "InputManager.h"
#include "Animation.h"

#define TURRET_MOB_ANIMATIONS 5

TurretMob::TurretMob(Vec2 pos, GameObject *focus)
    : focus(focus), animations(TURRET_MOB_ANIMATIONS),
      movementMode(TurretMobMovement::RESTING), previousPos(0, 0),
      destination(0, 0), restTimer()
{
    std::string files[TURRET_MOB_ANIMATIONS] = {
        "sprites/monsters/turretmob/TurretMobIdle.png",
        "sprites/monsters/turretmob/TurretMobWalkFront.png",
        "sprites/monsters/turretmob/TurretMobWalkFrontMirror.png",
        "sprites/monsters/turretmob/TurretMobWalkBack.png",
        "sprites/monsters/turretmob/TurretMobWalkBackMirror.png"};
    int frameCounts[TURRET_MOB_ANIMATIONS] = {7, 8, 8, 8, 8};
    float frameTimes[TURRET_MOB_ANIMATIONS] = {0.3, 0.3, 0.3, 0.3, 0.3};
    for (int i = 0; i < TURRET_MOB_ANIMATIONS; i++) {
        animations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }

    box.pos = pos;
    box.dim = Vec2(animations.GetCurrentWidth(), animations.GetCurrentHeight());
    hitbox.dim = Vec2(box.dim.x / 2, box.dim.y / 4);
    hitbox.pos = Vec2(box.pos.x + 35, box.pos.y + 80);
    attackHitbox.dim = Vec2(box.dim.x/3, box.dim.y/1.5);
    attackHitbox.pos = Vec2(box.pos.x + box.dim.x/3, box.pos.y + box.dim.y/4);

    hp = 100;
    rotation = 0;
}

void TurretMob::Render(void)
{
    animations.Render(box.pos.x, box.pos.y);

    int attackColor[4] = COLOR_ATTACK_HITBOX;
    if (Config::ATTACK_HITBOX_MODE)
        attackHitbox.RenderFilledRect(attackColor);
}

bool TurretMob::IsDead(void)
{
    return (hp <= 0);
}

void TurretMob::Update(float dt)
{
    // temporary suicide button
    if (InputManager::GetInstance().KeyPress(J_KEY))
        TakeDamage(8000);

    LookAtFocus();
    Movement(dt);
    Attack(dt);
    animations.Update(dt);
}

void TurretMob::NotifyCollision(GameObject &other, bool movement)
{
    if (other.Is("Bullet") || other.Is("Attack")) {
        Bullet &bullet = (Bullet &)other;
        if (!bullet.targetsPlayer)
            TakeDamage(10);
    } else if (movement && (!other.Is("Ball"))) {
        box.pos = previousPos;
        movementMode = TurretMobMovement::TRAPED;
    }
}

bool TurretMob::Is(std::string className)
{
    return ("TurretMob" == className);
}

void TurretMob::TakeDamage(float dmg)
{
    hp -= dmg;
    if (IsDead())
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            box.GetCenter(), 0, "sprites/monsters/turretmob/TurretMobDeath.png",
            7, 0.2, true));
}

void TurretMob::LookAtFocus(void)
{
    Vec2 lookVector = focus->box.GetCenter() - box.GetCenter();

    if (lookVector.y < 0) {
        if (lookVector.x >= 0)
            animations.SetCurrentState(BACK);
        else
            animations.SetCurrentState(BACK_MIRROR);
    } else {
        if (lookVector.x >= 0)
            animations.SetCurrentState(FRONT_MIRROR);
        else
            animations.SetCurrentState(FRONT);
    }
}

void TurretMob::Movement(float dt)
{
    Vec2 speed = Vec2(0, 0);

    if (movementMode == TurretMobMovement::RESTING) {
        animations.SetCurrentState(IDLE);
        restTimer.Update(dt);

        if (restTimer.Get() >= (Config::Rand(10, 35) / 10.0f)) {
            movementMode = TurretMobMovement::MOVING;
            destination = Vec2(Config::Rand(100, 250), 0);
            float angle = (float)(Config::Rand(0, 180) * M_PI) / 180.0f;
            destination = destination.Rotate(angle) + box.pos;
        }
    } else if (movementMode == TurretMobMovement::MOVING) {
        if (box.pos.DistanceFromPoint(destination) <= 5) {
            box.pos = destination;
            restTimer.Restart();
            movementMode = TurretMobMovement::RESTING;
            destination = Vec2(0, 0);
        } else {
            speed = (destination - box.pos).Norm() * 25 * dt;
            previousPos = box.pos;
            box.pos += speed;
        }

        if (Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this)) {
            box.pos = previousPos;
            movementMode = TurretMobMovement::TRAPED;
        }
    } else if (movementMode == TurretMobMovement::TRAPED) {
        destination = destination.Rotate(1 * M_PI);
        speed = (destination - box.pos).Norm() * 25 * dt;
        previousPos = box.pos;
        box.pos += speed;
        movementMode = TurretMobMovement::MOVING;
    }

    hitbox.pos = Vec2(box.pos.x + 35, box.pos.y + 80);
    attackHitbox.pos = Vec2(box.pos.x + box.dim.x/3, box.pos.y + box.dim.y/4);
}

void TurretMob::Attack(float dt)
{
    static Timer attackTimer = Timer();
    attackTimer.Update(dt);

    if (attackTimer.Get() >= Config::Rand(20, 60) / 10.0f) {
        Vec2 evaPos = focus->box.GetCenter();
        Vec2 boxVector = box.GetCenter();
        boxVector.y -= 10;
        boxVector.x -= 10;
        float angle = 0;

        evaPos -= box.GetCenter();
        angle = atan2(evaPos.y, evaPos.x);
        Bullet *b = new Bullet(boxVector, angle, 200, 1000,
                               "sprites/monsters/projectiles/BlueBombSpritesheet.png",
                               Vec2(-10, -10), Vec2(20, 20), 8, 0.3, true);

        Game::GetInstance()->GetCurrentState().AddObject(b);

        attackTimer.Restart();
    }
}

