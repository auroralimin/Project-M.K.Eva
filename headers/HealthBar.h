#pragma once

#include "Sprite.h"
#include "Vec2.h"

/**************************************************************************/ /**
  * The representation of the Health Bar.                                      *
  * Used by the players character, Eva.                                        *
  *****************************************************************************/
class HealthBar
{
public:
    /**
      * Initializes the HealthBar with parameters.
      * @param baseFile String containing the path to the baseFile sprite.
      * @param overlayFile String containing the path to the overlayFile sprite.
      */
    HealthBar(std::string baseFile, std::string overlayFile);

    /**
      * Renders the base, bar and overlay sprites.
      */
    void Render();

    /**
      * Updates the health bar sprite based on Eva's current hp.
      * @param hp Eva's current hp.
      */
    void Update(float hp);

private:
    Sprite base;
    Sprite bar;
    Sprite overlay;
};



