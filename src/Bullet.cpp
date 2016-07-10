#include "Bullet.h"
#include "Game.h"
#include "Config.h"
#include "Camera.h"
#include "Animation.h"

Bullet::Bullet(Vec2 pos, float angle, float speed, float maxDistance, float dmg,
               std::string sprite, Vec2 hitboxOffset, Vec2 hitboxDim,
               int frameCount, float frameTime, bool targetsPlayer)
    : sp(sprite, frameCount, frameTime),
      speed(speed * cos(angle), speed * sin(angle)), hitboxOffset(hitboxOffset),
      previousPos(pos), distanceLeft(maxDistance)
{
    this->dmg = dmg;
    this->targetsPlayer = targetsPlayer;

    box.pos = pos;
    box.dim = Vec2(sp.GetWidth(), sp.GetHeight());
    hitbox.dim = hitboxDim;
    hitbox.pos = box.pos + hitboxOffset;
    attackHitbox.dim = hitboxDim;
    attackHitbox.pos = box.pos + hitboxOffset;

    rotation = angle;
}

void Bullet::Update(float dt)
{
    bool collided = false;
    previousPos = box.pos;
    box.pos += speed * dt;

    if (Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this)) {
        collided = true;
        distanceLeft = 0;
        hitbox.pos = Vec2(box.pos.x + 5, previousPos.y + 35);
    }

    if (!collided) {
        sp.Update(dt);
        distanceLeft -= speed.Mag() * dt;
    }

    hitbox.pos = box.pos + hitboxOffset;
    attackHitbox.pos = box.pos + hitboxOffset;
}

void Bullet::Render()
{

    int color[4] = COLOR_HITBOX;
    if (Config::HITBOX_MODE)
        hitbox.RenderFilledRect(color);

    int attackColor[4] = COLOR_ATTACK_HITBOX;
    if (Config::ATTACK_HITBOX_MODE)
        attackHitbox.RenderFilledRect(attackColor);

    sp.Render(box.pos.x - box.dim.x / 2 - Camera::pos.x,
              box.pos.y - box.dim.y / 2 - Camera::pos.y, rotation * 180 / M_PI);
}

bool Bullet::IsDead()
{
    return (distanceLeft <= 0);
}

void Bullet::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR movement;

    if (targetsPlayer && other.Is("Eva")) {
        distanceLeft = 0;
    } else if ((!targetsPlayer) && (!other.Is("Eva")) &&
               (!other.Is("Bullet"))) {
        distanceLeft = 0;
    }

    if ((!targetsPlayer) && (distanceLeft == 0)) {
        Vec2 otherPos = other.box.GetCenter();
        otherPos -= box.GetCenter();
        float angle = atan2(otherPos.y, otherPos.x);
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            box.pos, angle * 180 / M_PI, "sprites/eva/attack/BULLET_IMPACT.png",
            2, 0.1, true));
    } else if ((targetsPlayer) && (distanceLeft == 0)) {
        Vec2 otherPos = other.box.GetCenter();
        otherPos -= box.GetCenter();
        float angle = atan2(otherPos.y, otherPos.x);
        Game::GetInstance()->GetCurrentState().AddObject(new Animation(
            box.pos, angle * 180 / M_PI,
            "sprites/monsters/projectiles/BlueBomb_Impact.png", 2, 0.1, true));
    }
}

bool Bullet::Is(std::string className)
{
    return ("Bullet" == className);
}

void Bullet::TakeDamage(float dmg)
{
    UNUSED_VAR dmg;
}

