#include "Cutscene.h"
#include "Config.h"

Cutscene::Cutscene(Vec2 pos, std::string name, int nFrames, float frameTime,
        std::string soundFile, bool oneTimeOnly) : name(name), currentFrame(0),
    nFrames(nFrames),frameTime(frameTime), timer(), isDead(false),
    oneTimeOnly(oneTimeOnly), playSound(false), soundStopped(true)
{
    box.pos = pos;
    sp = new Sprite[nFrames];
    for (int i = 0; i < nFrames; ++i)
        sp[i].Open("cutscene/" + name + "/" + std::to_string(i + 1) + ".png");
    box.dim.x = sp[0].GetWidth();
    box.dim.y = sp[0].GetHeight();

    if (soundFile != "") {
        playSound = true;
        sound.Open(soundFile);
    }
}

void Cutscene::Update(float dt)
{
    timer.Update(dt);
    if (timer.Get() / 1000.0f >= frameTime) {
        currentFrame++;
        timer.Restart();
    }

    if (currentFrame >= nFrames) {
        if (oneTimeOnly) {
            if (!soundStopped) {
                sound.Stop();
                soundStopped = true;
            }
            isDead = true;
        } else {
            currentFrame = 0;
        }
    }
}

void Cutscene::Render(void)
{
    if (playSound) {
        sound.Play(1);
        playSound = false;
        soundStopped = false;
    }

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
    if (!soundStopped)
        sound.Stop();
    isDead = true;    
}

void Cutscene::SetPos(Vec2 pos)
{
    box.pos = pos;
}

