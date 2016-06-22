#pragma once

#include "State.h"
#include "LevelMap.h"

/***************************************************************************/ /**
  * States that generates procedural generates maps and displays them
  ******************************************************************************/
class ProceduralState : public State
{
  public:
    /**
     * Initialises a Procedural State loading a procedural generated map
     * layout.
     */
    ProceduralState(void);

    /**
     * Procedural generates more maps according to input.
     * @param dt time elapsed between th current and the last frame
     */
    void Update(float dt);

    /**
     * Renders map layout.
     */
    void Render(void);

    /**
     * Do nothing. It is necessary to inherit from State.
     */
    void Pause(void);

    /**
     * Do nothing. It is necessary to inherit from State.
     */
    void Resume(void);

    /**
     * Do nothing. It is necessary to inherit from State.
     */
    bool IsCollidingWithWall(GameObject *obj);

    /**
     * Do nothing. It is necessary to inherit from State.
     */
    void CheckMovementCollisions();

  private:
    unsigned int seed;
};

