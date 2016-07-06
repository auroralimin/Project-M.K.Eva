#pragma once

#include "GameObject.h"
#include "Room.h"
#include "AnimationFSM.h"

class Monster : public GameObject
{
    public:
        /**
         * It allows a instance of a derivade class to be deleted.
         * This is done through a pointer to this class.
         */
        ~Monster(void);
        void Render(void);
        bool IsDead(void);

    protected:
        AnimationFSM animations;
        Room *room;

        void NotifyDeath(void);
};

