#include "AttackClass.h"
#include "Config.h"

AttackClass::AttackClass(Vec2 pos, int orientation, std::string sprite,
               int frameCount, float frameTime)
{
    timeElapsed.Restart();
    sp = Sprite(sprite, frameCount, frameTime);
    box.pos = pos;
    box.dim.x = sp.GetWidth();
    box.dim.y = sp.GetHeight();
    duration = frameCount*frameTime;
    hitbox.dim = Vec2(box.dim.x/2, box.dim.y);
    hitbox.pos = Vec2(box.pos.x, box.pos.y);
    switch (orientation) {
    case 5:
        rotation = -90;
        hitbox.dim = Vec2(2.5*box.dim.x/8, 1.5*box.dim.y);
        hitbox.pos = Vec2(box.pos.x + 3.5*box.dim.x/10, box.pos.y - box.dim.y);
        break;
    case 6:
        rotation = 90;
        hitbox.dim = Vec2(2.5*box.dim.x/8, 1.5*box.dim.y);
        hitbox.pos = Vec2(box.pos.x + 3.5*box.dim.x/10, box.pos.y + box.dim.y/2);
        break;
    case 7:
        rotation = 0;
        hitbox.dim = Vec2(5.5*box.dim.x/10, box.dim.y);
        hitbox.pos = Vec2(box.pos.x, box.pos.y);
        break;
    case 8:
        rotation = 0;
        hitbox.dim = Vec2(5*box.dim.x/10, box.dim.y);
        hitbox.pos = Vec2(box.pos.x + 5*box.dim.x/10, box.pos.y);
        break;
    default:
        rotation = 0;
        hitbox.dim = Vec2(box.dim.x, box.dim.y);
        hitbox.pos = Vec2(box.pos.x, box.pos.y);
        break;
    }
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
    //TODO: make it only hit enemies once
}

bool AttackClass::Is(std::string className)
{
    return ("Attack" == className);
}

void AttackClass::TakeDamage(float dmg)
{
}
