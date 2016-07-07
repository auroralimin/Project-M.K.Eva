#include "Animation.h"
#include "Camera.h"
#include "Config.h"
#include "Game.h"
#include "Eva.h"

#define EVA_SPAWN_POSITION_X 192
#define EVA_SPAWN_POSITION_Y 103


Animation::Animation(Vec2 pos, float rotation, std::string sprite,
                     int frameCount, float frameTime, bool ends, int rows)
    : sp(sprite, frameCount, frameTime, rows), oneTimeOnly(ends),
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
    sp.Update(dt);    
}

void Animation::Render(void)
{
    sp.Render(box.pos.x - Camera::pos.x - box.dim.x / 2,
              box.pos.y - Camera::pos.y - box.dim.y / 2, rotation);
}

bool Animation::IsDead(void)
{
    bool isDead = (oneTimeOnly && (sp.GetCurrentFrame() == sp.GetFrameCount() - 1));
    if (isDead && Is("Animation:sprites/eva/drawer/DRAWER-EVA.png"))
        Game::GetInstance()->GetCurrentState().AddObject(new Eva(Vec2(EVA_SPAWN_POSITION_X, EVA_SPAWN_POSITION_Y)));

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

