#pragma once

#include "Monster.h"
#include "Timer.h"

/*******************************************************************************
  * The representation of the MekaBug enemy                                    *
  * This enemy chases down its focus, usually the player's character, Eva.     *
  * When it is close enough, attacks the player with its eletrical current.    *
  *****************************************************************************/
class MekaBugMonster : public Monster
{
  public:
    /**
      * Initializes the MekaBug with parameters.
      * @param room Pointer to the room where it belongs to.
      * @param pos A Vec2 vector containing its spwan posistion.
      * @param focus Pointer to the object that is focused on. Usually its the
      * player's character, Eva.
      */
    MekaBugMonster(Room *room, Vec2 pos, GameObject *focus);

    /**
      * Sets the current sprite based on the state of the MekaBug.
      * Updates the timer with the damage invicibilty frames, its position, the
      * attackHitbox's and the hitbox position.
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
     * Reduces the MekaBug's hp.
     * @param dmg Value that will be reduced from the MekaBug's hp
     */
    void TakeDamage(float dmg = 1);

  private:
    enum MekaBugMonsterMovement { RESTING, MOVING, TRAPED };
    enum MekaBugMonsterState { PASSIVE, AGRESSIVE };

    GameObject *focus;
    MekaBugMonsterMovement movState;
    Vec2 previousPos;
    bool stuck;
    Timer restTimer, stuckTimer, attackTimer;

    bool wasHit;
    Timer hitTimer;
    void MovementAndAttack(float dt);
};

