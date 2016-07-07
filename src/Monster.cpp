#include "Monster.h"
#include "Config.h"
#include "Camera.h"

Monster::~Monster(void)
{
    room->DecreaseNMonsters();
}

void Monster::Render(void)
{
    animations.Render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y);
    int attackColor[4] = COLOR_ATTACK_HITBOX;
    if (Config::ATTACK_HITBOX_MODE)
        attackHitbox.RenderFilledRect(attackColor);
    
    int color[4] = COLOR_HITBOX;
    if (Config::HITBOX_MODE)
        hitbox.RenderFilledRect(color);
}

bool Monster::IsDead(void)
{
    return (hp <= 0);
}

