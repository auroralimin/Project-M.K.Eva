#pragma once

#include <iostream>

#include "Sprite.h"
#include "Timer.h"

class Door
{
    public:
        enum DoorState {WALL, CLOSED, OPENED, INVISIBLE};

        Door(void);
        void Load(int direction, DoorState state, std::string path);
        void Update(float dt);
        void Render(void);
        void SetCurrentState(int currentState);
        int GetCurrentState(void);

    private:
        int state, direction;
        Timer timer;
        bool isTransitioning;
        std::string path;
        Sprite sps[2];
};

