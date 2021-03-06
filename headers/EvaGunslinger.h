#pragma once

#include "EvaClass.h"
#include "Timer.h"
#include "HealthBar.h"

/***************************************************************************/ /**
  * Eva's ranged class
  ******************************************************************************/

class EvaGunslinger : public EvaClass
{
  public:
    /**
     * Initialize the animationFSM with the class's sprites and initialize
     * attributes
     */
    EvaGunslinger();

    /**
     * Update the animation of the current state, timers and cooldowns
     * @param dt time elapsed between frames
     * @param hp Eva's current HP
     */
    void Update(float dt, float hp);

    /**
     * Shoots a bullet in the given direction
     * @param pos Eva's current position
     * @param direction bullet's movement direction
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

