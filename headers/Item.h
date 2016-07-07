#pragma once

#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"

class Item : public GameObject
{
    public:
        Item(std::string name, Vec2 pos);
        void Render(void);
        void Update(float dt);
        bool IsDead(void);
        void NotifyCollision(GameObject &other, bool movement);
        bool Is(std::string className);
        void TakeDamage(float dmg = 1);
        
    private:
        Sprite sp;
        std::string name;
        bool isDead;
};

