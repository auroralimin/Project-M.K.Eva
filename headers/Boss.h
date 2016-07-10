#pragma once

#include "GameObject.h"
#include "AnimationFSM.h"
#include "BossHealthBar.h"
#include "Timer.h"

/*******************************************************************************
  * The representation of the Boss enemy                                       *
  * Currently its not fully implemented.                                       *
  *****************************************************************************/
class Boss : public GameObject
{
public:
    /**
      * Initializes the Boss with parameters.
      * @param pos A Vec2 vector with its spwan position.
      */
    Boss(Vec2 pos);

    /**
      * Renders the Boss current sprite. If HITBOX_MODE and/or
      * ATTACK_HITBOX_MODE is currently true, also renders the
      * hitbox and attackHitbox.
      */
    void Render();

    /**
      * Returns whether the Boss is dead or not.
      * @return Returns true if the Boss hp is equal or less
      * than 0, false otherwise.
      */
    bool IsDead();

    /**
      * Sets the current sprite. Updates the health bar.
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
     * Reduces the Boss's hp.
     * @param dmg Value that will be reduced from the Boss's hp
     */
    void TakeDamage(float dmg = 1);

private:
    AnimationFSM animations[2];
    BossHealthBar healthBar;
    int currentPhase;
    int currentState;


};
