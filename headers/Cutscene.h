#pragma once

#include "GameObject.h"
#include "Sprite.h"
#include "Timer.h"
#include "Sound.h"

/***************************************************************************/ /**
  * Creates a game cutscene given a directory full of images.
  * It can be played repeatly or one time only.
  ******************************************************************************/
class Cutscene : public GameObject
{
    public:
        
        /**
         * Initialize a cutscene given arguments.
         * @param pos a Vec2 with the position where the frames will start to be
         * rendered
         * @param name a string with the name of the cutscene directory
         * @param nFrames an int containing the number od frames of the cutscenes
         * @param frameTime an int containing the time between frames
         * @param soundFile a string containing the sound tname to be played
         * during the cutscene
         * @param oneTimeOnly a bool indicating if the cutscene will be played
         * in loop or one time only
         */
        Cutscene(Vec2 pos, std::string name, int nFrames, float frameTime = 0.1,
                std::string soundFile = "", bool oneTimeOnly = true);

        /**
         * Given a delta time, updates the current cutscene frame.
         * Thus, the cutscene appears fluidly and according to the framecount.
         * @param dt a float argument containing the game delta time
         */
        void Update(float dt);

        /**
         * Renders the current cutscene frame.
         */
        void Render(void);

        /**
         * Checks if the cutscene has ended
         * @return return if the cutscne has ended
         */
        bool IsDead(void);

        /**
         * This method does nothing.
         * It is implemented only as a requirement of inheriting from GameObject.
         * @param unused argument
         * @param unused argument
         */
        void NotifyCollision(GameObject &other, bool movement);

        /**
         * Checks if the class name given as argument is the same as the
         * cutscene name.
         * @param className a string argument with the name of a class
         * @return If className is the same as this cutscene name
         */

        bool Is(std::string className);

        /**
         * This method does nothing.
         * It is implemented only as a requirement of inheriting from GameObject.
         */
        void TakeDamage(float dmg = 1);

        /**
         * Kills an animation, evem if has not ended yet.
         */
        void Kill(void);

        /**
         * Sets the animation to be rendered position.
         */
        void SetPos(Vec2 pos);

    private:
        std::string name;
        int currentFrame, nFrames;
        float frameTime;
        Timer timer;
        bool isDead, oneTimeOnly, playSound, soundStopped;
        Sound sound;
        Sprite *sp;
};

