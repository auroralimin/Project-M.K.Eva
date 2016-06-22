#pragma once

#include "State.h"
#include "LevelMap.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Music.h"

/***************************************************************************/ /**
  * FirstLevel level managment state.
  ******************************************************************************/
class FirstLevelState : public State
{
  public:
    /**
     * Initialises a FirstLevel State loading intro map and Eva character.
     */
    FirstLevelState(Vec2 evaPos);

    /**
     * Sets room based on Eva position on the map.
     * @param dt time elapsed between th current and the last frame
     */
    void Update(float dt);

    /**
     * Renders map room and state list of objects.
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

    void CheckMovementCollisions();

  private:
    unsigned int seed;
    LevelMap map;
    bool isEvaDead;
    Music music;

    void UpdateEva(int i);
};

