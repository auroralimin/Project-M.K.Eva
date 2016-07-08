#pragma once

#include "Monster.h"
#include "Timer.h"

/*****************************************
 * The representation of the turret enemy
 ****************************************/
class TurretMonster : public Monster
{
    public:
        TurretMonster(Room *room, Vec2 pos, GameObject *focus);
        void Update(float dt);
        void NotifyCollision(GameObject &other, bool movement);
        bool Is(std::string className);
        void TakeDamage(float dmg = 1);

    private:
        GameObject *focus;
        Timer hitTimer, timer;
        bool wasHit;

        void ShootPattern1(void);
        void ShootPattern2(void);
};

