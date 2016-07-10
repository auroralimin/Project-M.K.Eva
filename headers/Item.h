#pragma once

#include "GameObject.h"
#include "Vec2.h"
#include "Sprite.h"

/**************************************************************************/ /**
  * An game item abstraction
  *****************************************************************************/
class Item : public GameObject
{
  public:
    /**
     * Initializes an Item object given arguments.
     * @param name a string containing the item name/identification
     * @param pos a Vec2 with the position of the item
     */
    Item(std::string name, Vec2 pos);

    /**
     * Renders the item sprite.
     */
    void Render(void);

    /**
     * This method does nothing.
     * It is implemented only as a requirement of inheriting from GameObjetc.
     */
    void Update(float dt);

    /**
     * Checks if the item was already picked
     * @return returns if the item was picked
     */
    bool IsDead(void);

    /**
     * If eva collided with the item, declare the item dead.
     * @param other a pointer to a GameObject that collided with the item
     * @param movement unused argument
     */
    void NotifyCollision(GameObject &other, bool movement);

    /**
     * Checks if the class name given as argument is the same the item name.
     * @param className a string argument with the name of a class
     * @return If className is the same as this item name
     */
    bool Is(std::string className);

    /**
     * This method does nothing.
     * It is implemented only as a requirement of inheriting from GameObjetc.
     */
    void TakeDamage(float dmg = 1);

  private:
    Sprite sp;
    std::string name;
    bool isDead;
};

