#pragma once

#include "GameObject.h"
#include "Room.h"
#include "AnimationFSM.h"

/*******************************************************************************
  * The representation of a enemy monster in the game.                         *
  * The enemies in the game will inherit from this class.                      *
  *****************************************************************************/
class Monster : public GameObject
{
    public:
        /**
         * It allows a instance of a derivade class to be deleted.
         * This is done through a pointer to this class.
         */
        ~Monster(void);

        /**
          * Renders the Monster current sprite. If HITBOX_MODE and/or
          * ATTACK_HITBOX_MODE is currently true, also renders the
          * hitbox and attackHitbox.
          */
        void Render(void);
    
        /**
          * Returns whether the Monster is dead or not.
          * @return Returns true if the Monster hp is equal or less
          * than 0, false otherwise.
          */
        bool IsDead(void);

    protected:
        AnimationFSM animations;
        Room *room;

        void NotifyDeath(void);
};

