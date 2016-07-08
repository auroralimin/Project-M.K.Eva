#include "Animation.h"
#include "Camera.h"
#include "Config.h"
#include "Game.h"
#include "Eva.h"

Animation::Animation(Vec2 pos, float rotation, std::string sprite,
                     int frameCount, float frameTime, bool ends, int rows)
    : sp(sprite, frameCount, frameTime, rows), oneTimeOnly(ends), isDead(false),
    is("Animation:" + sprite)
{
    animationImg = "";
    box.pos = pos;
    this->rotation = rotation;
    box.dim.x = sp.GetWidth();
    box.dim.y = sp.GetHeight();
}

void Animation::Update(float dt)
{
    int oldFrame = sp.GetCurrentFrame();
    sp.Update(dt);    
    if (oldFrame > 0 && sp.GetCurrentFrame() == 0 && oneTimeOnly)
        isDead = true;
}

void Animation::Render(void)
{
    if (!isDead)
        sp.Render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y,
                rotation);
}

bool Animation::IsDead(void)
{
    return isDead;
}

void Animation::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR other;
    UNUSED_VAR movement;
    // D0 NOTHING
}

bool Animation::Is(std::string className)
{
    return (className == is);
}

void Animation::TakeDamage(float dmg)
{
    UNUSED_VAR dmg;
    // D0 NOTHING
}

