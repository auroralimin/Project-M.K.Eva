#ifndef EVA_H
#define EVA_H

#include "GameObject.h"
#include "AnimationFSM.h"

class Eva : public GameObject
{
public:
    /**
     * Default initializes an empty AnimationFSM, and initializes member
     * variables with default values;
     */
    Eva();

    /**
     * Initializes Eva with parameters
     * @param x position of eva in the x axis
     * @param y position of eva in the y axis
     * @param idleFile path to the idle animation sprite sheet
     * @param upFile path to the moving up animation sprite sheet
     * @param downFile path to the moving down animation sprite sheet
     * @param leftFile path to the moving left animation sprite sheet
     * @param rightFile path to the moving right animation sprite sheet
     * @param frameCount number of frames for the spritesheets
     * @param frameTime duration of each frame
     */
    Eva(int x, int y, std::string idleFile, std::string upFile, std::string downFile,
        std::string leftFile, std::string rightFile, int frameCount = 1,
        float frameTime = 1.0f, int moveSpeed = 150);

    ~Eva();

    /**
     * Renders the current animation
     */
    void Render();

    /**
     * Sets the current animation based on input and updates sprites
     * @param dt time elapsed between th current and the last frame
     */
    void Update(float dt);

    /**
     * Returns if eva's hp reach 0 or below
     * @return returns true if eva's hp reached 0 or below, returns false
     * otherwise
     */
    bool IsDead();

    /**
     * Reacts to a collision
     * @param other reference define reaction to the collision
     */
    void NotifyCollision(GameObject &other);

    /**
     * Returns if this class is the class indicated by className
     * @param className name of the class to be tested
     * @return if className is equal to this class' name then returns true,
     * returns false otherwise
     */
    bool Is(std::string className);

    /**
     * Reduces eva's hp
     * @param dmg value that will be reduced from eva's hp
     */
    void TakeDamage(int dmg = 1);

    /**
     * Changes the file from which the idle sprite will be created and
     * resets the sprite
     * @param file new sprite file
     */
    void SetIdleFile(std::string file);

    /**
     * Changes the file from which the moving up sprite will be created and
     * resets the sprite
     * @param file new sprite file
     */
    void SetMoveUpFile(std::string file);

    /**
     * Changes the file from which the moving down sprite will be created and
     * resets the sprite
     * @param file new sprite file
     */
    void SetMoveDownFile(std::string file);

    /**
     * Changes the file from which the moving left sprite will be created and
     * resets the sprite
     * @param file new sprite file
     */
    void SetMoveLeftFile(std::string file);

    /**
     * Changes the file from which the moving right sprite will be created and
     * resets the sprite
     * @param file new sprite file
     */
    void SetMoveRightFile(std::string file);

    /**
     * Sets the frameTime and resets all sprites to accomodate the new frameTime
     * @param time value to be attributed to frameTime
     */
    void SetFrameTime(float time);

    /**
     * Sets the frameCount and resets all sprites to accomodate the new
     * frameCount
     * @param count value to be attributed to frameCount
     */
    void SetFrameCount(int count);

private:
    std::string idleFile;
    std::string moveUpFile;
    std::string moveDownFile;
    std::string moveLeftFile;
    std::string moveRightFile;
    float frameTime;
    AnimationFSM evaAnimations;
    int moveSpeed;

};

#endif // EVA_H
