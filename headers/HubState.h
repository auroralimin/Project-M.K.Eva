#pragma once

#include "State.h"
#include "GameObject.h"
#include "LevelMap.h"
#include "Music.h"

/***************************************************************************/ /**
  * Hub level managment state.
  ******************************************************************************/
class HubState : public State
{
  public:
    /**
     * Initialises a Hub Menu State and Eva character.
     */
    HubState(void);

    /**
     * Class destructor. Currently stops the song playing.
     */
    ~HubState(void);

    /**
     * Checks if Eva went to another room and change state based on that room
     * @param dt time elapsed between th current and the last frame
     */
    void Update(float dt);

    /**
     * Renders the morgue scenario
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
     * Checks if some object is colliding with the current room wall.
     */
    bool IsCollidingWithWall(GameObject *o);

    /**
     * Update state array of objects, including checking if Eva changed room.
     * @param dt time elapsed between th current and the last frame
     */
    void UpdateArray(float dt);

    /**
     * This method does nothing.
     * It is implemented only as a requirement of inheriting from GameObjetc.
     */
    void CheckMovementCollisions();

  private:
    LevelMap map;
    Music music;

    void UpdateEva(int i);
};

