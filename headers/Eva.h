#pragma once

#include "Vec2.h"
#include "GameObject.h"
#include "EvaBase.h"
#include "EvaClass.h"
#include "Timer.h"

#include <memory>

/***************************************************************************/ /**
  * The representation of the game main character object.
  * Eva used the game engine to implement a lot of actions, including moving and
  * changing class.
  ******************************************************************************/
class Eva : public GameObject
{
  public:
    /**
     * Enum to represent eva's classes.
     */
    enum Classes { BASE, SAMURAI, GUNSLINGER, DECKER };

    /**
     * Initializes Eva with parameters.
     * @param pos a Vec2 contains eva's initial position
     */
    Eva(Vec2 pos, bool hasAllClasses);

    /**
     * Renders the current animation.
     */
    void Render();

    /**
     * Sets the current animation based on input, updates sprites and gets
     * attack and movement input.
     * @param dt time elapsed between th current and the last frame
     */
    void Update(float dt);

    /**
     * Returns if eva's hp reach 0 or below.
     * @return returns true if eva's hp reached 0 or below, returns false
     * otherwise
     */
    bool IsDead();

    /**
     * Reacts to a collision.
     * @param other reference define reaction to the collision
     */
    void NotifyCollision(GameObject &other, bool movement);

    /**
     * Returns if this class is the class indicated by className.
     * @param className name of the class to be tested
     * @return if className is equal to this class' name then returns true,
     * returns false otherwise
     */
    bool Is(std::string className);

    /**
     * Reduces eva's hp.
     * @param dmg value that will be reduced from eva's hp
     */
    void TakeDamage(float dmg = 1);

    /**
     * Returns which eva death animation file is being used
     * @return the path to the death animation file
     */
    std::string GetEvaDeath(void);

    /**
     * Method to be called by class unlock items at intro. Increments the number
     * of available classes and immediately changes to the new class.
     */
    void IncreaseAvailableClasses(void);

    enum Animations {
        IDLE,
        MOVING_UP,
        MOVING_LEFT,
        MOVING_DOWN,
        MOVING_RIGHT,
        ATTACKING_UP,
        ATTACKING_LEFT,
        ATTACKING_DOWN,
        ATTACKING_RIGHT
    };

  private:
    const std::string classes[4] = {"BASE", "SAMURAI", "GUN", "DECKER"};
    float *frameTimes;
    int *frameCounts;
    int moveSpeed;
    Vec2 previousPos;
    std::string evaDeath;
    std::vector<std::unique_ptr<EvaClass>> evaClasses;
    unsigned int currentClass;
    Timer spawnDelayTimer, hitTimer;
    bool doneSpawning, wasHit;
    int availableClasses;

    void SetClass(Classes c);
};

