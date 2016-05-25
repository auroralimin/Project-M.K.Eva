#ifndef ANIMATIONFSM_H
#define ANIMATIONFSM_H

#include "Sprite.h"

class AnimationFSM
{
public:
    AnimationFSM();

    AnimationFSM(std::string idleFile, std::string moveUpFile,
                 std::string moveDownFile, std::string moveLeftFile,
                 std::string moveRightFile, int frameCount, float frameTime);

    /**
     * Renders the sprite according to the current state
     * @param x a int argument containing the x of the render position
     * @param y a int argument containing the y of the render position
     */
    void Render(int x, int y);

    /**
     * Updates the sprites so the animation happens
     * @param dt time passed between frames
     */
    void Update(float dt);

    /**
     * This enum defines the possible states of an animation
     */
    enum AnimationState {
        IDLE,
        MOVING_UP,
        MOVING_DOWN,
        MOVING_LEFT,
        MOVING_RIGHT
    };

    /**
     * Sets the current state of the animation
     * @param state the state to become the current state
     */
    void SetCurrentState(AnimationState state);

    /**
     * Returns the current state of the animation
     * @return returns the value of the current state
     */
    AnimationState GetCurrentState();

    /**
     * Sets the idle animation sprite
     * @param file file to be opened
     * @param frameCount number of frames
     * @param frameTime duration of each frame
     */
    void SetIdleAnimation(std::string file, int frameCount, float frameTime);

    /**
     * Sets the moving up animation sprite
     * @param file file to be opened
     * @param frameCount number of frames
     * @param frameTime duration of each frame
     */
    void SetMoveUpAnimation(std::string file, int frameCount, float frameTime);

    /**
     * Sets the moving down animation sprite
     * @param file file to be opened
     * @param frameCount number of frames
     * @param frameTime duration of each frame
     */
    void SetMoveDownAnimation(std::string file,
                              int frameCount, float frameTime);

    /**
     * Sets the moving left animation sprite
     * @param file file to be opened
     * @param frameCount number of frames
     * @param frameTime duration of each frame
     */
    void SetMoveLeftAnimation(std::string file,
                              int frameCount, float frameTime);

    /**
     * Sets the moving right animation sprite
     * @param file file to be opened
     * @param frameCount number of frames
     * @param frameTime duration of each frame
     */
    void SetMoveRightAnimation(std::string file,
                               int frameCount, float frameTime);

    /**
     * Returns the width of a frame
     * @return returns sprite width/frameCount
     */
    int GetSpriteWidth();

    /**
     * Returns the height of a frame
     * @return returns sprite height
     */
    int GetSpriteHeight();

private:
    AnimationState currentState;
    Sprite idle;
    Sprite moveUp;
    Sprite moveDown;
    Sprite moveLeft;
    Sprite moveRight;

};

#endif // ANIMATIONFSM_H
