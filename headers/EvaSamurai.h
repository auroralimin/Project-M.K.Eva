#pragma once

#include "EvaClass.h"
#include "Timer.h"
#include "HealthBar.h"

/***************************************************************************/ /**
  * Eva's melee class
  ******************************************************************************/

class EvaSamurai : public EvaClass
{
  public:
    /**
     * Initialize the animationFSM with the class's sprites and initialize
     * attributes
     */
    EvaSamurai();

    /**
     * Update the animation of the current state, timers and cooldowns
     * @param dt time elapsed between frames
     * @param hp Eva's current HP
     */
    void Update(float dt, float hp);

    /**
     * Slashes in the given direction
     * @param pos Eva's current position
     * @param direction direction to witch Eva will slash
     */
    void Attack(Vec2 pos, int direction);

    /**
     * Execute death animation
     * @param pos Eva's current position
     */
    void Die(Vec2 pos);

    /**
     * Renders the class' current animation, HUD and minimap
     * @param x render position along the x axis
     * @param y render position along the y axis
     */
    void Render(float x, float y);

  private:
    Timer atkTimer;
    Timer atkCooldown;

    HealthBar healthBar;
    Sprite minimap;
};

