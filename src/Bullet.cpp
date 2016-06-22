#include "Bullet.h"
#include "Game.h"
#include "Config.h"

Bullet::Bullet(Vec2 pos, float angle, float speed, float maxDistance,
               std::string sprite, Vec2 hitboxOffset, Vec2 hitboxDim,
               int frameCount, float frameTime, bool targetsPlayer)
    : sp(sprite, frameCount, frameTime),
      speed(speed * cos(angle), speed * sin(angle)), hitboxOffset(hitboxOffset),
      previousPos(pos), distanceLeft(maxDistance)
{
    this->targetsPlayer = targetsPlayer;

    box.pos = pos;
    box.dim = Vec2(sp.GetWidth(), sp.GetHeight());
    hitbox.dim = hitboxDim;
    hitbox.pos = box.pos + hitboxOffset;

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
}

void Bullet::Render()
{
    int color[4] = COLOR_HITBOX;
    if (Config::HITBOX_MODE)
        hitbox.RenderFilledRect(color);

    sp.Render(box.pos.x - box.dim.x / 2, box.pos.y - box.dim.y / 2,
              rotation * 180 / M_PI);
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
    } else if ((!targetsPlayer) && (!other.Is("Eva"))) {
        distanceLeft = 0;
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

