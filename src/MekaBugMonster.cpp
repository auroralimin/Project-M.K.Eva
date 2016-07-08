#include "MekaBugMonster.h"
#include "Eva.h"
#include "Config.h"
#include "Game.h"
#include "Animation.h"
#include "Bullet.h"
#include "Collision.h"

#define MEKABUG_ANIMATIONS 2
#define HITBOX_DIM_OFFSET_Y 2
#define HITBOX_POS_OFFSET_Y 35
#define AH_DIM_OFFSET_Y 1.5
#define AH_POS_OFFSET_Y box.dim.y/3

MekaBugMonster::MekaBugMonster(Room *room, Vec2 pos, GameObject *focus)
    : focus(focus), movState(MekaBugMonsterMovement::RESTING), previousPos(pos),
    stuck(false), restTimer(), stuckTimer(), attackTimer(), hitTimer()
{
    this->room = room;
    std::string files[MEKABUG_ANIMATIONS] = {
        "sprites/monsters/mekabug/MEKABUG_SPRITESHEET.png",
        "sprites/monsters/mekabug/MEKABUG_ATTACK_SPRITESHEET.png"};
    int frameCounts[MEKABUG_ANIMATIONS] = {6, 5};
    float frameTimes[MEKABUG_ANIMATIONS] = {0.3, 0.3};
    animations =
        AnimationFSM(MEKABUG_ANIMATIONS, files, frameCounts, frameTimes);

    box.pos = pos;
    box.dim = Vec2(animations.GetCurrentWidth(), animations.GetCurrentHeight());
    hitbox.dim = Vec2(box.dim.x, box.dim.y/HITBOX_DIM_OFFSET_Y);
    hitbox.pos = Vec2(box.pos.x, box.pos.y + HITBOX_POS_OFFSET_Y);
    attackHitbox.dim = Vec2(box.dim.x, box.dim.y/AH_DIM_OFFSET_Y);
    attackHitbox.pos = Vec2(box.pos.x, box.pos.y + AH_POS_OFFSET_Y);

    hp = 50;
    rotation = 0;
    wasHit = false;
    hitTimer.Restart();
}

void MekaBugMonster::Update(float dt)
{
    if (wasHit)
        hitTimer.Update(dt);
    if (hitTimer.Get() >= MONSTER_DAMAGE_DELAY){
        hitTimer.Restart();
        wasHit = false;
    }

    MovementAndAttack(dt);
    animations.Update(dt);
}

void MekaBugMonster::NotifyCollision(GameObject &other, bool movement)
{
    if (other.Is("Attack")) {
        Bullet &bullet = (Bullet &)other;
        if (!bullet.targetsPlayer)
            TakeDamage(other.dmg/2);
    } else if (other.Is("Bullet")) {
        Bullet &bullet = (Bullet &)other;
        if (!bullet.targetsPlayer)
            TakeDamage(other.dmg*2);
    } else if (movement && (!other.Is("Ball"))) {
        box.pos = previousPos;
        if (other.Is("MekaBugMonster"))
            stuck = true;
    }
}

bool MekaBugMonster::Is(std::string className)
{
    return ("MekaBugMonster" == className);
}

void MekaBugMonster::TakeDamage(float dmg)
{
    if (!wasHit){
        hp -= dmg;
        wasHit = true;
    }
    if (IsDead())
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            box.pos, 0, "sprites/monsters/mekabug/MEKABUG_DEATH.png", 3,
            0.5, true));
}

void MekaBugMonster::MovementAndAttack(float dt)
{
    if (focus != nullptr) {
        Vec2 speed = Vec2(0, 0);
        attackTimer.Update(dt);

        if (movState == MekaBugMonsterMovement::RESTING) {
            restTimer.Update(dt);

            if (restTimer.Get() >= Config::Rand(10, 25) / 10.0f) {
                movState = MekaBugMonsterMovement::MOVING;
                animations.SetCurrentState(MekaBugMonsterState::PASSIVE);
            }
        } else if (movState == MekaBugMonsterMovement::MOVING) {
            Vec2 evaPos = focus->box.GetCenter();
            if (Collision::IsColliding(focus->hitbox, hitbox, focus->rotation,
                                       rotation)) {
                movState = MekaBugMonsterMovement::RESTING;
                animations.SetCurrentState(MekaBugMonsterState::AGRESSIVE);
                restTimer.Restart();
                if ((attackTimer.Get() >= 1)) {
                    focus->TakeDamage(10);
                    attackTimer.Restart();
                }
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
                movState = MekaBugMonsterMovement::RESTING;
                restTimer.Restart();
            }
        }

        hitbox.pos = Vec2(box.pos.x, box.pos.y + HITBOX_POS_OFFSET_Y);
        attackHitbox.pos = Vec2(box.pos.x, box.pos.y + AH_POS_OFFSET_Y);
    } else {
        movState = MekaBugMonsterMovement::RESTING;
        animations.SetCurrentState(MekaBugMonsterState::PASSIVE);
    }
}

