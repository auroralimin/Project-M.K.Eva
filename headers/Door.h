#pragma once

#include <iostream>

#include "Sprite.h"
#include "Timer.h"

/***************************************************************************/ /**
  * An abstraction of a door.
  * Used to implement the opening/closing/sealing door actions.
  ******************************************************************************/
class Door
{
    public:

        /**
         * An abstraction of wall states.
         */
        enum DoorState {WALL, CLOSED, OPENED, INVISIBLE};

        /**
         * Initialize doors attributes with default values.
         */
        Door(void);

        /**
         * Loads doors attributes.
         * @param direction an int containing if it is a down, left, up or right
         * kind of door.
         * @param state a DoorState containg the door state
         * @param path the path to the assets related with the door
         */
        void Load(int direction, DoorState state, std::string path);

        /**
         * Given a delta time, updates the timer to possibly playing animations.
         * @param dt a float argument containing the game delta time
         */
        void Update(float dt);

        /**
         * Depending on the state, possbly renders a door image asset.
         */
        void Render(void);

        /**
         * Sets the current state.
         * @param currentState an int with the current state to be.
         */
        void SetCurrentState(int currentState);

        /**
         * Gets the current state.
         * @return returns the current state.
         */
        int GetCurrentState(void);

    private:
        int state, direction;
        Timer timer;
        bool isTransitioning;
        std::string path;
        Sprite sps[2];
};

