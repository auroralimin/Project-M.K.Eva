#pragma once
#include "GameObject.h"
#include "Sprite.h"
#include "Vec2.h"
#include "Timer.h"

/***************************************************************************/ /**
  * Creates a game animation given a sprite sheet.
  * This animation can be played
  * once or repeatedly.
  ******************************************************************************/
class Animation : public GameObject
{
  public:
    /**
     * Reads an animation sprite sheet of a given file.
     * Sets all information needed to compose an animation.
     * @param pos a Vec2 argument with the animation position
     * @param rotation a float argument with the animation rotation
     * @param sprite a string argument that contains the sprite file path
     * @param frameCount a int argument with the animation sprite number os
     * frames
     * @param frameTime a float argument with the frames time
     * @param end a bool argument to check if the animation is played once or
     * repeatedly
     */
    Animation(Vec2 pos, float rotation, std::string sprite, int frameCount = 1,
              float frameTime = 0.1, bool ends = true);

    /**
     * Given a delta time, updates the current animation frame.
     * Thus, the animation appears fluidly and according to the framecount.
     * @param dt a float argument containing the game delta time
     */
    void Update(float dt);

    /**
     * Renders the current animation frame.
     */
    void Render(void);

    /**
     * Returns if the animation is still being played.
     * It will always return false if the
     * animation is setted to be played repeatedly.
     * @return If the animation is dead or not
     */
    bool IsDead(void);

    /**
     * This method does nothing.
     * It is implemented only as a requirement of inheriting from GameObjetc.
     */
    void NotifyCollision(GameObject &other, bool movement);

    /**
     * Checks if the class name given as argument is the same as "Animation".
     * @param className a string argument with the name of a class
     * @return If className is the same as this class name
     */
    bool Is(std::string className);

    /**
     * This method does nothing.
     * It is implemented only as a requirement of inheriting from GameObjetc.
     */
    void TakeDamage(float dmg = 1);

    /**
     * Contains the file path to an sprite sheet to create a object animation.
     */
    std::string animationImg;

  private:
    Sprite sp;
    Timer endTimer;
    float timeLimit;
    bool oneTimeOnly;
    std::string is;
};

