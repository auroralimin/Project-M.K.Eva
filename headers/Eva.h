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
     * @brief Update
     * @param dt
     */
    void Update(float dt);

    bool IsDead();
    void NotifyCollision(GameObject &other);
    bool Is(std::string className);
    void TakeDamage(int dmg = 1);

    void SetIdleFile(std::string file);
    void SetMoveUpFile(std::string file);
    void SetMoveDownFile(std::string file);
    void SetMoveLeftFile(std::string file);
    void SetMoveRightFile(std::string file);
    void SetFrameTime(float time);
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
