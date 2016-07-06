#include "AttackClass.h"
#include "Config.h"
#include "Camera.h"

AttackClass::AttackClass(Vec2 pos, Vec2 hitboxOffset, Vec2 hitboxDim, float dmg,
                         std::string sprite, int frameCount,
                         float frameTime)
    : timeElapsed(),
      duration(frameCount * frameTime)
{
    damage = dmg;
    if (sprite == ""){
        sp = Sprite();
        box.dim = hitboxDim;
    }
    else{
        sp = Sprite(sprite, frameCount, frameTime);
        box.dim = Vec2(sp.GetWidth(), sp.GetHeight());
    }
    box.pos = pos;

    rotation = 0;
    attackHitbox.dim = hitboxDim;
    attackHitbox.pos = pos + hitboxOffset;
}

void AttackClass::Render()
{
    int attackColor[4] = COLOR_ATTACK_HITBOX;
    if (Config::ATTACK_HITBOX_MODE)
        attackHitbox.RenderFilledRect(attackColor);

    sp.Render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y, rotation);
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
    // TODO: make it only hit enemies once
    
    if (!(other.Is("Bullet") || other.Is("Eva")))
        other.TakeDamage(attackDamage);
    
}

bool AttackClass::Is(std::string className)
{
    return ("Attack" == className);
}

void AttackClass::TakeDamage(float dmg)
{
    UNUSED_VAR dmg;
    // do nothing
}

