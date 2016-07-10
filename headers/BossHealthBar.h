#pragma once
#include "Sprite.h"

/**************************************************************************/ /**
  * The representation of the Boss's Health Bar.                               *
  *****************************************************************************/
class BossHealthBar
{
  public:
    /**
      * Initializes the BossHealthBar.
      */
    BossHealthBar();

    /**
      * Renders the health bar sprite.
      */
    void Render();

    /**
      * Updates the health bar sprite based on the Boss's current hp.
      * @param hp Boss's current hp.
      */
    void Update(float hp);

  private:
    Sprite bar;
};

