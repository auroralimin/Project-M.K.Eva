#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"

/**************************************************************************/ /**
 * Creates an Class attack
 *****************************************************************************/
class AttackClass : public GameObject
{
  public:
    /**
     * Initializes the AttackClass attributes given arguments.
     * @param pos a Vec2 with the attack position
     * @param hitboxOffset a Vec2 with the hitbox offset
     * @param hitboxDim a Vec2 with the hitbox dim
     * @param dmg a float with how much damage this attack gives
     * @param sprite a string containing the sprite name
     * @param frameCount a int with the frames count
     * @param frameTime a float with the frames time
     */
    AttackClass(Vec2 pos, Vec2 hitboxOffset, Vec2 hitboxDim, float dmg,
                std::string sprite = "", int frameCount = 1,
                float frameTime = 1);

    /**
     * Renders the Attack.
     */
    void Render();

    /**
     * Checks if the Attack is over.
     * @return returns if the attack is over
     */
    bool IsDead();

    /**
     * Given a delta time, updates the attack animation.
     * @param dt a float argument containing the game delta time
     */
    void Update(float dt);

    /**
     * If is Bullet or Eva, make they deal with the collision.
     */
    void NotifyCollision(GameObject &other, bool movements);

    /**
     * This method does nothing.
     * It is implemented only as a requirement of inheriting from GameObjetc.
     */
    bool Is(std::string className);

    /**
     * This method does nothing.
     * It is implemented only as a requirement of inheriting from GameObjetc.
     */
    void TakeDamage(float dmg = 1);

    /**
     * The attack damage.
     */
    float damage;

  private:
    Sprite sp;
    float attackDamage;
    Timer timeElapsed;
    float duration;
};

