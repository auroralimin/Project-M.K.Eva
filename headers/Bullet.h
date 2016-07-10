#pragma once

#include "GameObject.h"
#include "Sprite.h"

/*****************************************************************
  * Representation of the Bullets that can be fired in the game. *
  ****************************************************************/
class Bullet : public GameObject
{
  public:
    /**
      * Initializes the Bullet with parameters.
      * @param pos A Vec2 vector containing its spwan position.
      * @param angle Angle of the vector containing direction it was fired.
      * @param speed Speed of the bullet.
      * @param maxDistance Maximum travel distance of the Bullet, without 
      * colliding with anything.
      * @param dmg The damage dealt by the Bullet.
      * @param sprite String contaning the path of the sprite used in the 
      * Bullet.
      * @param hitboxOffset A Vec2 containing the offset of the hitbox of the
      * Bullet.
      * @param hitboxDim A Vec2 containing the dimensions of the hitbox. X is
      * width, while Y is the height.
      * @param frameCount Number of frames of the sprite.
      * @param frameTime Time spent on each frame.
      * @param targetsPlayer Indicates if the Bullet was fired by an enemy or
      * by the player.
      */
    Bullet(Vec2 pos, float angle, float speed, float maxDistance, float dmg,
           std::string sprite, Vec2 hitboxOffset, Vec2 hitboxDim,
           int frameCount = 1, float frameTime = 1, bool targetsPlayer = false);

    /**
      * Renders the Bullet current frame of the sprite. If HITBOX_MODE and/or
      * ATTACK_HITBOX_MODE is currently true, also renders the
      * hitbox and attackHitbox.
      */
    void Render();

    /**
      * Returns whether the Bullet is dead.
      * @return Returns true if the Bullet traveled its maximum distance, or
      * collided with an object. Returns false otherwise.
      */
    bool IsDead();

    /**
      * Updates the Bullet's distance left for the maximum distance it can
      * travel, and updates the sprite.
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
      * Does nothing.
      */
    void TakeDamage(float dmg = 1);

    /**
      * Boolean indicanting if the Bullet was fired by an enemy or by the 
      * player.
      */
    bool targetsPlayer;

  private:
    Sprite sp;
    Vec2 speed, hitboxOffset, previousPos;
    float distanceLeft;
};

