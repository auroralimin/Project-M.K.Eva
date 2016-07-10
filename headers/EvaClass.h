#pragma once

#include "AnimationFSM.h"
#include "Vec2.h"
#include <string>

/***************************************************************************/ /**
  * A virtual class that is the base to all Eva class implementations
  ******************************************************************************/

class EvaClass
{
  public:
    /**
     * Default class constructor. Initializes an empty animationFSM
     */
    EvaClass(void);

    /**
     * Allows an instance of child classes to have a destructor
     */
    virtual ~EvaClass(void)
    {
    }

    /**
     * When implemented should update the object
     * @param dt time elapsed between frames
     * @param hp Eva's current HP
     */
    virtual void Update(float dt, float hp) = 0;

    /**
     * When implemented should execute the class' attack
     * @param pos Eva's current position
     * @param direction direction of the attack
     */
    virtual void Attack(Vec2 pos, int direction) = 0;

    /**
     * Execute death animation
     * @param pos Eva's current position
     */
    virtual void Die(Vec2 pos) = 0;

    /**
     * Renders the class' current animation
     * @param x render position along the x axis
     * @param y render position along the y axis
     */
    virtual void Render(float x, float y);

    /**
     * Sets the animationFSM current state
     * @param state the new state to be set
     */
    virtual void SetCurrentState(int state);

    /**
     * returns whether an attack is in progress or not
     * @return true if an attack is in progress, false otherwise
     */
    virtual bool IsAttacking(void);

    /**
     * returns whether an attack can be made or not
     * @return true if an attack can be made, false otherwise
     */
    virtual bool AttackReady(void);

    /**
     * The class' movement speed attribute
     */
    int movSpeed;

    /**
     * The class' attack damage attribute
     */
    int atk;

    /**
     * The class' defense attribute
     */
    int def;

    /**
     * The class' attack speed attribute
     */
    float atkSpeed;

    /**
     * The class' set of animations in an AnimationFSM
     */
    AnimationFSM animations;

  protected:
    int currentState;
    std::string *files;
    float *frameTimes;
    int *frameCounts;
    bool isAttacking;
    bool atkReady;
};

