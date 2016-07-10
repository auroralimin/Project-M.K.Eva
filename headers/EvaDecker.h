#pragma once

#include "EvaClass.h"
#include "Timer.h"
#include "HealthBar.h"

/***************************************************************************/ /**
  * Eva's AOE attack class
  ******************************************************************************/

class EvaDecker : public EvaClass
{
  public:
    /**
     * Initialize the animationFSM with the class's sprites and initialize
     * attributes
     */
    EvaDecker();

    /**
     * Update the animation of the current state, timers and cooldowns
     * @param dt time elapsed between frames
     * @param hp Eva's current HP
     */
    void Update(float dt, float hp);

    /**
     * Attacks arround the player's position
     * @param pos Eva's current position
     * @param direction unused variable at this implementation
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
    bool atkStarted;
    Vec2 atkPos;

    void Shockwave(Vec2 pos);

    HealthBar healthBar;
    Sprite minimap;
};

