#pragma once

#include "EvaClass.h"

/***************************************************************************/ /**
  * Eva whithout any other class to be used at the hub and the beggining of the
  * intro
  ******************************************************************************/

class EvaBase : public EvaClass
{
  public:
    /**
     * Initialize the animationFSM with the class's sprites and initialize
     * attributes
     */
    EvaBase(void);

    /**
     * Updates the animation of the current state
     * @param dt time elapsed between frames
     * @param hp Eva's current HP
     */
    void Update(float dt, float hp);

    /**
     * Does nothing for this class
     * @param pos Eva's current position
     * @param direction the attack's direction
     */
    void Attack(Vec2 pos, int direction);

    /**
     * Does nothing for this class
     * @param pos Eva's current class
     */
    void Die(Vec2 pos);
};

