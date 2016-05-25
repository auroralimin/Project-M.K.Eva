#include "AnimationFSM.h"

AnimationFSM::AnimationFSM(): idle(), moveUp(), moveDown(), moveLeft(),
                              moveRight()
{
    currentState = IDLE;
}

AnimationFSM::AnimationFSM(std::string idleFile, std::string moveUpFile,
                           std::string moveDownFile, std::string moveLeftFile,
                           std::string moveRightFile, int frameCount,
                           float frameTime):
    idle(idleFile, frameCount, frameTime),
    moveUp(moveUpFile, frameCount, frameTime),
    moveDown(moveDownFile, frameCount, frameTime),
    moveLeft(moveLeftFile, frameCount, frameTime),
    moveRight(moveRightFile, frameCount, frameTime)

{
    currentState = IDLE;
}

void AnimationFSM::Render(int x, int y)
{
    switch (currentState) {
    case IDLE:
        idle.Render(x, y);
        break;
    case MOVING_UP:
        moveUp.Render(x, y);
        break;
    case MOVING_DOWN:
        moveDown.Render(x, y);
        break;
    case MOVING_LEFT:
        moveLeft.Render(x, y);
        break;
    case MOVING_RIGHT:
        moveRight.Render(x, y);
        break;
    default:
        idle.Render(x, y);
        break;
    }
}

void AnimationFSM::Update(float dt)
{
    switch (currentState) {
    case IDLE:
        idle.Update(dt);
        break;
    case MOVING_UP:
        moveUp.Update(dt);
        break;
    case MOVING_DOWN:
        moveDown.Update(dt);
        break;
    case MOVING_LEFT:
        moveLeft.Update(dt);
        break;
    case MOVING_RIGHT:
        moveRight.Update(dt);
        break;
    default:
        idle.Update(dt);
        break;
    }
}

void AnimationFSM::SetCurrentState(AnimationFSM::AnimationState state)
{
    //Resets all the animations when the state changes
    if (currentState != state) {
        currentState = state;
        idle.SetFrame(0);
        moveUp.SetFrame(0);
        moveDown.SetFrame(0);
        moveLeft.SetFrame(0);
        moveRight.SetFrame(0);
    }
}

AnimationFSM::AnimationState AnimationFSM::GetCurrentState()
{
    return currentState;
}

void AnimationFSM::SetIdleAnimation(std::string file, int frameCount,
                                    float frameTime)
{
    idle.Open(file);
    idle.SetFrameCount(frameCount);
    idle.SetFrameTime(frameTime);
}

void AnimationFSM::SetMoveUpAnimation(std::string file, int frameCount,
                                      float frameTime)
{
    moveUp.Open(file);
    moveUp.SetFrameCount(frameCount);
    moveUp.SetFrameTime(frameTime);
}

void AnimationFSM::SetMoveDownAnimation(std::string file, int frameCount,
                                        float frameTime)
{
    moveDown.Open(file);
    moveDown.SetFrameCount(frameCount);
    moveDown.SetFrameTime(frameTime);
}

void AnimationFSM::SetMoveLeftAnimation(std::string file, int frameCount,
                                        float frameTime)
{
    moveLeft.Open(file);
    moveLeft.SetFrameCount(frameCount);
    moveLeft.SetFrameTime(frameTime);
}

void AnimationFSM::SetMoveRightAnimation(std::string file, int frameCount,
                                         float frameTime)
{
    moveRight.Open(file);
    moveRight.SetFrameCount(frameCount);
    moveRight.SetFrameTime(frameTime);
}

int AnimationFSM::GetSpriteWidth()
{
    return idle.GetWidth();
}

int AnimationFSM::GetSpriteHeight()
{
    return idle.GetHeight();
}
