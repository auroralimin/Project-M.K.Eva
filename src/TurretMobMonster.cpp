#include <math.h>

#include "TurretMobMonster.h"
#include "Eva.h"
#include "Bullet.h"
#include "Game.h"
#include "Config.h"
#include "InputManager.h"
#include "Animation.h"

#define TURRET_MOB_ANIMATIONS 5
#define HITBOX_DIM_OFFSET_X 2
#define HITBOX_DIM_OFFSET_Y 4
#define HITBOX_POS_OFFSET_X 35
#define HITBOX_POS_OFFSET_Y 80
#define AH_DIM_OFFSET_X 3
#define AH_DIM_OFFSET_Y 1.5
#define AH_POS_OFFSET_X box.dim.x/3
#define AH_POS_OFFSET_Y box.dim.y/4

TurretMobMonster::TurretMobMonster(Room *room, Vec2 pos, GameObject *focus)
    : focus(focus), movementMode(TurretMobMonsterMovement::RESTING), previousPos(0, 0),
      destination(0, 0), restTimer()
{
    this->room = room;
    std::string files[TURRET_MOB_ANIMATIONS] = {
        "sprites/monsters/turretmob/TurretMobIdle.png",
        "sprites/monsters/turretmob/TurretMobWalkFront.png",
        "sprites/monsters/turretmob/TurretMobWalkFrontMirror.png",
        "sprites/monsters/turretmob/TurretMobWalkBack.png",
        "sprites/monsters/turretmob/TurretMobWalkBackMirror.png"};
    int frameCounts[TURRET_MOB_ANIMATIONS] = {7, 8, 8, 8, 8};
    float frameTimes[TURRET_MOB_ANIMATIONS] = {0.3, 0.3, 0.3, 0.3, 0.3};
    animations =
        AnimationFSM(TURRET_MOB_ANIMATIONS, files, frameCounts, frameTimes);

    box.pos = pos;
    box.dim = Vec2(animations.GetCurrentWidth(), animations.GetCurrentHeight());
    hitbox.dim = Vec2(box.dim.x/HITBOX_DIM_OFFSET_X , box.dim.y/HITBOX_DIM_OFFSET_Y);
    hitbox.pos = Vec2(box.pos.x + HITBOX_POS_OFFSET_X, box.pos.y + HITBOX_POS_OFFSET_Y);
    attackHitbox.dim = Vec2(box.dim.x/AH_DIM_OFFSET_X, box.dim.y/AH_DIM_OFFSET_Y);
    attackHitbox.pos = Vec2(box.pos.x + AH_POS_OFFSET_X, box.pos.y + AH_POS_OFFSET_Y);

    hp = 100;
    rotation = 0;
}

void TurretMobMonster::Update(float dt)
{
    // temporary suicide button
    if (InputManager::GetInstance().KeyPress(J_KEY))
        TakeDamage(8000);

    if (focus != nullptr) {
        LookAtFocus();
        Movement(dt);
        Attack(dt);
    }
    animations.Update(dt);
}

void TurretMobMonster::NotifyCollision(GameObject &other, bool movement)
{
    if (other.Is("Bullet") || other.Is("Attack")) {
        Bullet &bullet = (Bullet &)other;
        if (!bullet.targetsPlayer)
            TakeDamage(10);
    } else if (movement && (!other.Is("Ball"))) {
        box.pos = previousPos;
        movementMode = TurretMobMonsterMovement::TRAPED;
    }
}

bool TurretMobMonster::Is(std::string className)
{
    return ("TurretMobMonster" == className);
}

void TurretMobMonster::TakeDamage(float dmg)
{
    hp -= dmg;
    if (IsDead())
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            box.pos, 0, "sprites/monsters/turretmob/TurretMobDeath.png",
            7, 0.2, true));
}

void TurretMobMonster::LookAtFocus(void)
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

void TurretMobMonster::Movement(float dt)
{
    Vec2 speed = Vec2(0, 0);

    if (movementMode == TurretMobMonsterMovement::RESTING) {
        animations.SetCurrentState(IDLE);
        restTimer.Update(dt);

        if (restTimer.Get() >= (Config::Rand(10, 35) / 10.0f)) {
            movementMode = TurretMobMonsterMovement::MOVING;
            destination = Vec2(Config::Rand(100, 250), 0);
            float angle = (float)(Config::Rand(0, 180) * M_PI) / 180.0f;
            destination = destination.Rotate(angle) + box.pos;
        }
    } else if (movementMode == TurretMobMonsterMovement::MOVING) {
        if (box.pos.DistanceFromPoint(destination) <= 5) {
            box.pos = destination;
            restTimer.Restart();
            movementMode = TurretMobMonsterMovement::RESTING;
            destination = Vec2(0, 0);
        } else {
            speed = (destination - box.pos).Norm() * 25 * dt;
            previousPos = box.pos;
            box.pos += speed;
        }

        if (Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this)) {
            box.pos = previousPos;
            movementMode = TurretMobMonsterMovement::TRAPED;
        }
    } else if (movementMode == TurretMobMonsterMovement::TRAPED) {
        destination = destination.Rotate(1 * M_PI);
        speed = (destination - box.pos).Norm() * 25 * dt;
        previousPos = box.pos;
        box.pos += speed;
        movementMode = TurretMobMonsterMovement::MOVING;
    }

    hitbox.pos = Vec2(box.pos.x + HITBOX_POS_OFFSET_X, box.pos.y + HITBOX_POS_OFFSET_Y);
    attackHitbox.pos = Vec2(box.pos.x + AH_POS_OFFSET_X, box.pos.y + AH_POS_OFFSET_Y);
}

void TurretMobMonster::Attack(float dt)
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

