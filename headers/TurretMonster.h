#pragma once

#include "Monster.h"
#include "Timer.h"

/**************************************************************************/ /**
 * The representation of the Turret enemey.                                    *
 * This enemy is stationary and fire's at its focus, usually the player's      *
 * character, Eva.                                                             *
 ******************************************************************************/
class TurretMonster : public Monster
{
    public:

        /**
          * Initializes the Turret with parameters.
          * @param room Pointer to the room where it belongs to.
          * @param pos A Vec2 vector containing its spwan posistion.
          * @param focus Pointer to the object that is focused on. Usually its the
          * player's character, Eva.
          */
        TurretMonster(Room *room, Vec2 pos, GameObject *focus);

        /**
          * Updates the sprite and the timers.
          * If enough time has passed, shoots the player.
          * @param dt Time elapsed between the current and the last frame.
          */
        void Update(float dt);

        /**
          * Reacts to collisions based on the object it collided with.
          * @param other reference to the define location of the collided object.
          * @param movement Bool that indicates if the collision was based on a
          * movement or an attack.
          */
        void NotifyCollision(GameObject &other, bool movement);

        /**
         * Returns if this class is the class indicated by className.
         * @param className Name of the class to be tested.
         * @return If className is equal to this class' name then returns true,
         * returns false otherwise.
         */
        bool Is(std::string className);

        /**
         * Reduces the Turret's hp.
         * @param dmg Value that will be reduced from the Turret's hp
         */
        void TakeDamage(float dmg = 1);

    private:
        GameObject *focus;
        Timer hitTimer, timer;
        bool wasHit;

        void ShootPattern1(void);
        void ShootPattern2(void);
};

