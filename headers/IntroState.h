#pragma once

#include "State.h"
#include "LevelMap.h"
#include "GameObject.h"
#include "Vec2.h"
#include "Music.h"

/***************************************************************************/ /**
  * Intro level managment state.
  ******************************************************************************/
class IntroState : public State
{
  public:
    /**
     * Initialises a Intro State loading intro map and Eva character.
     */
    IntroState(Vec2 evaPos);

    /**
     * Class destructor. Currently stops the song playing.
     */
    ~IntroState();

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
    LevelMap map;
    Music music;
    bool evaDead;

    void UpdateEva(int i);
};

