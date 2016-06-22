#include "AttackClass.h"
#include "Config.h"

AttackClass::AttackClass(Vec2 pos, Vec2 hitboxOffset, Vec2 hitboxDim,
        int orientation, std::string sprite, int frameCount, float frameTime) :
    sp(sprite, frameCount, frameTime),
    timeElapsed(), duration(frameCount*frameTime)
{
    box.pos = pos;
    box.dim = Vec2(sp.GetWidth(), sp.GetHeight());
    hitbox.dim = Vec2(box.dim.x/2, box.dim.y);
    hitbox.pos = Vec2(box.pos.x, box.pos.y);

    std::cout << orientation << std::endl;
    rotation = (90*orientation);
    hitbox.dim = hitboxDim;
    hitbox.pos = pos + hitboxOffset;
}

void AttackClass::Render()
{
    int color[4] = COLOR_HITBOX;
    if (Config::HITBOX_MODE)
        hitbox.RenderFilledRect(color);

    sp.Render(box.pos.x, box.pos.y, rotation);
}

bool AttackClass::IsDead()
{
    return (timeElapsed.Get() >= duration);
}

void AttackClass::Update(float dt)
{
    timeElapsed.Update(dt);
    sp.Update(dt);
}

void AttackClass::NotifyCollision(GameObject &other, bool movements)
{
    UNUSED_VAR other;
    UNUSED_VAR movements;
    //TODO: make it only hit enemies once
}

bool AttackClass::Is(std::string className)
{
    return ("Attack" == className);
}

void AttackClass::TakeDamage(float dmg)
{
    UNUSED_VAR dmg;
    //do nothing
}

