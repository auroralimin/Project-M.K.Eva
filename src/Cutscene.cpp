#include "Cutscene.h"
#include "Config.h"

Cutscene::Cutscene(Vec2 pos, std::string name, int nFrames, float frameTime,
        bool oneTimeOnly) : name(name), currentFrame(0), nFrames(nFrames),
    frameTime(frameTime), timer(), isDead(false), oneTimeOnly(oneTimeOnly)
{
    box.pos = pos;
    sp = new Sprite[nFrames];
    for (int i = 0; i < nFrames; ++i)
        sp[i].Open("cutscene/" + name + "/" + std::to_string(i + 1) + ".png");
    box.dim.x = sp[0].GetWidth();
    box.dim.y = sp[0].GetHeight();
}

void Cutscene::Update(float dt)
{
    timer.Update(dt);
    if (timer.Get() / 1000.0f >= frameTime) {
        currentFrame++;
        timer.Restart();
    }

    if (currentFrame >= nFrames) {
        if (oneTimeOnly)
            isDead = true;
        else
            currentFrame = 0;
    }
}

void Cutscene::Render(void)
{
    if (!isDead)
        sp[currentFrame].Render(box.pos.x, box.pos.y);
}

bool Cutscene::IsDead(void)
{
    return isDead;
}

void Cutscene::NotifyCollision(GameObject &other, bool movement)
{
    UNUSED_VAR other;
    UNUSED_VAR movement;
    //do nothing
}

bool Cutscene::Is(std::string className)
{
    return (className == name + "_cutscene");
}

void Cutscene::TakeDamage(float dmg)
{
    UNUSED_VAR dmg;
    //do nothing
}

void Cutscene::Kill(void)
{
    isDead = true;    
}

void Cutscene::SetPos(Vec2 pos)
{
    box.pos = pos;
}

