#pragma once

#include "Monster.h"
#include "Timer.h"

/*********************************************************
  * The representation of one of the enemies in the game.*
  * This enemy is managed by the class BallsManager, so  *
  * its actions are always syncronized with all of the   *
  * other Ball's in the room.                            *
  *********************************************************/
class BallMonster : public Monster
{
  public:
    /**
      * Initializes the Ball with parameters.
      * @param room Pointer to the room where it belongs to.
      * @param pos A Vec2 vector containing its spwan posistion.
      */
    BallMonster(Room *room, Vec2 pos);

    /**
      * Sets the current sprite based on the state of the Ball.
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
     * Reduces the Ball's hp.
     * @param dmg Value that will be reduced from the Ball's hp
     */
    void TakeDamage(float dmg = 1);

    /**
      * Returns if the Ball is inside a wall or colliding with a wall.
      * @returns True if the Ball is inside a wall, or colliding with one.
      * False otherwise.
      */
    bool IsInsideWall();

    /**
      * Sets the current state of the Ball.
      * @param state New state to be set.
      */
    void SetCurrentState(int state);

  private:
    Vec2 previousPos;
    Timer hitTimer;
    bool wasHit;
};

