#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Sound.h"

class Cutscene : public GameObject
{
    public:
        Cutscene(Vec2 pos, std::string name, int nFrames, float frameTime = 0.1,
                std::string soundFile = "", bool oneTimeOnly = true);
        void Update(float dt);
        void Render(void);
        bool IsDead(void);
        void NotifyCollision(GameObject &other, bool movement);
        bool Is(std::string className);
        void TakeDamage(float dmg = 1);
        void Kill(void);
        void SetPos(Vec2 pos);

    private:
        std::string name;
        int currentFrame, nFrames;
        float frameTime;
        Timer timer;
        bool isDead, oneTimeOnly, playSound, soundStopped;
        Sound sound;
        Sprite *sp;
};

