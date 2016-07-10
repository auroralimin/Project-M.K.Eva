#pragma once

#include <vector>

#include "BallMonster.h"
#include "Timer.h"

/**************************************************************************/ /**
  * The representation of the Balls Manager                                    *
  * This manager syncronizes all of the animations and attacks of all the      *
  * Balls in the room its set in.                                              *
  *****************************************************************************/
class BallsManager : public GameObject
{
  public:
    /**
      * Initializes the Manager with parameters.
      * @param room Pointer to the Room where it belongs to.
      * @param focus Pointer to the object that is focused on. Usually its the
      * player's character, Eva.
      */
    BallsManager(Room *room, GameObject *focus);

    /**
      * Creates and adds a Ball to the ballArray and returns that Ball.
      * @return Returns the Ball that was created.
      */
    BallMonster **AddBall(void);

    /**
      * Does nothing.
      */
    void Render();

    /**
      * Returns whether the Manager's ballArray is empty or not.
      * @returns Returns true if the Manager's ballArray is empty, false
      * otherwise.
      */
    bool IsDead();

    /**
      * Updates and sets the state of all the Balls in the ballArray based
      * on what the Balls should do.
      * @param dt Time elapsed between the current and the last frame.
      */
    void Update(float dt);
    
    /**
      * Does nothing.
      */
    void NotifyCollision(GameObject &other, bool movement);
    
    /**
     * Returns if this class is the class indicated by className.
     * @param className Name of the class to be tested.
     * @return If className is equal to this class' name then returns true,
     * returns false otherwise.
     */
    bool Is(std::string className);

    /**
      * Does nothing.
      */
    void TakeDamage(float dmg = 1);

    /**
      * Removes the dead Balls from the ballArray.
      */
    void ClearDeadBalls();

  private:
    enum BallsState { RESTING, WARNING, ATTACKING };

    Room *room;
    GameObject *focus;
    unsigned int currentState;
    std::vector<BallMonster *> ballArray;
    Timer timer;

    void SetCurrentState(int state);
    void RandTeleport();
};

