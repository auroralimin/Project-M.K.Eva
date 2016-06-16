#include "AnimationFSM.h"


AnimationFSM::AnimationFSM(int nAnimations)
{
    this->nAnimations = nAnimations;
    for (int i = 0; i < nAnimations; ++i)
        animationsArray.emplace_back(new Sprite());
    currentState = 0;
}

AnimationFSM::AnimationFSM(int nAnimations, std::string files[],
                           int frameCount[], float frameTime[])
{
    this->nAnimations = nAnimations;
    for (int i = 0; i < nAnimations; ++i)
        animationsArray.emplace_back(new Sprite(files[i],
                                                frameCount[i], frameTime[i]));
    currentState = 0;
}

void AnimationFSM::Render(int x, int y)
{
    animationsArray[currentState].get()->Render(x, y);
}

void AnimationFSM::Update(float dt)
{
    animationsArray[currentState].get()->Update(dt);
}

void AnimationFSM::SetCurrentState(int state)
{
    //Resets all the animations when the state changes
    if (currentState != state) {
        currentState = state;
        for (int i = 0; i < nAnimations; ++i)
			animationsArray[i].get()->SetFrame(0);
    }
}

int AnimationFSM::GetCurrentState()
{
    return currentState;
}

void AnimationFSM::SetNAnimations(int nAnimations)
{
    this->nAnimations = nAnimations;
}

void AnimationFSM::SetAnimation(int index, std::string file, int frameCount,
                                    float frameTime)
{
    animationsArray[index].get()->SetFrameCount(frameCount);
    animationsArray[index].get()->SetFrameTime(frameTime);
    animationsArray[index].get()->Open(file);
}

int AnimationFSM::GetSpriteWidth()
{
    return animationsArray[0].get()->GetWidth();
}

int AnimationFSM::GetSpriteHeight()
{
    return animationsArray[0].get()->GetHeight();
}

