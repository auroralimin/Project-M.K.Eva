#pragma once

#include "Monster.h"
#include "Timer.h"

/**************************************************************************/ /**
  * The representation of the TurretMob enemy                                  *
  * This enemy wander aimless around the room while facing and shooting        *
  * the player.                                                                *
  *****************************************************************************/
class TurretMobMonster : public Monster
{
  public:
    /**
      * Initializes the TurretMob with parameters.
      * @param room The Room where it belongs to.
      * @param pos A Vec2 vector containing its swpan location.
      * @param focus Pointer to the object that is focused on. Usually its the
      * player's character, Eva.
      */
    TurretMobMonster(Room *room, Vec2 pos, GameObject *focus);

    /**
      * Sets the current sprite based on the position relatively to the
      * focus position. Moves and updates the TurretMob position, and
      * attack the focus.
      * Updates the timer with the damage invicibilty frames, and the
      * attackHitbox's position.
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
     * Reduces the TurretMob's hp.
     * @param dmg Value that will be reduced from the TurretMob's hp
     */
    void TakeDamage(float dmg = 1);

  private:
    enum TurretMobMonsterMovement { RESTING, MOVING, TRAPED };
    enum TurretMobMonsterState { IDLE, FRONT, FRONT_MIRROR, BACK, BACK_MIRROR };

    GameObject *focus;
    TurretMobMonsterMovement movementMode;
    Vec2 previousPos, destination;
    Timer restTimer, attackTimer, hitTimer;
    bool wasHit;

    void LookAtFocus(void);
    void Movement(float dt);
    void Attack(float dt);
};

