#include "Monster.h"
#include "Config.h"

Monster::~Monster(void)
{
    room->DecreaseNMonsters();
}

void Monster::Render(void)
{
    animations.Render(box.pos.x, box.pos.y);

    int attackColor[4] = COLOR_ATTACK_HITBOX;
    if (Config::ATTACK_HITBOX_MODE)
        attackHitbox.RenderFilledRect(attackColor);
}

bool Monster::IsDead(void)
{
    return (hp <= 0);
}

