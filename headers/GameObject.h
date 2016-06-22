#pragma once
#include <iostream>
#include "Rect.h"

/***************************************************************************/ /**
  * A virtual class that is the base for creating game objects..
  ******************************************************************************/
class GameObject
{
  public:
    /**
     * Contains the position and the dimentions of the object.
     */
    Rect box;

    /**
     * Contains the position and the dimentions of the object hitbox.
     */
    Rect hitbox;

    /**
     * Contains the rotation of the object.
     */
    float rotation;

    /**
     * Contains the counter of how many frames a object animation has.
     */
    int frameCount;

    /**
     * It allows a instance of a derivade class to be deleted.
     * This is done through a pointer to this class.
     */
    virtual ~GameObject(void){};

    /**
     * When implemented, it should render the object.
     */
    virtual void Render(void) = 0;

    /**
     * If possible, when implemented it should check if the object is dead.
     * @return if the object is dead
     */
    virtual bool IsDead(void) = 0;

    /**
     * When implemented, it should update the objetc.
     * @param dt a float argument contaning the delta time
     */
    virtual void Update(float dt) = 0;

    /**
     * If possible, when implemented it should process collisions.
     */
    virtual void NotifyCollision(GameObject &other, bool movement) = 0;

    /**
     * When implemented, it should check if a given string has the same
     * name as the derivated classes.
     * @param className a string with the name of the class being checked
     * @return If className is the same as this class name
     */
    virtual bool Is(std::string className) = 0;

    /**
     * If possible, when implemented it should make the object take damage.
     * @param dmg a int argument containing the damage value
     */
    virtual void TakeDamage(float dmg = 1) = 0;

  protected:
    float hp;
};

