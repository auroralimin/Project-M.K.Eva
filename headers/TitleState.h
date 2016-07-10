#include "State.h"
#include "Sprite.h"
#include "Text.h"
#include "Timer.h"
#include "Cutscene.h"

class TitleState : public State
{
    public:
        /**
         * Initialises a Title State loading the cutscenes and the initial
         * screen.
         */
        TitleState(void);

        /**
         * Updates the state based if the cutscenes are happening.
         * @param dt time elapsed between th current and the last frame
         */
        void Update(float dt);

        /**
         * Renders either an initial cutscene or the initial screen with the
         * game logo.
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
         * @param obj unused argument
         */
        bool IsCollidingWithWall(GameObject *obj);

        /**
         * Do nothing. It is necessary to inherit from State.
         */
        void CheckMovementCollisions(void);

    private:
        Cutscene cutscene, titleFadeIn;
        Sprite title, msg;
        Timer timer;
};

