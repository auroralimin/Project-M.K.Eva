#include "AnimationFSM.h"

AnimationFSM::AnimationFSM(void)
{
    this->nAnimations = 0;
    currentState = 0;
}

AnimationFSM::AnimationFSM(int nAnimations, std::string files[],
                           int frameCount[], float frameTime[])
{
    this->nAnimations = nAnimations;
    for (int i = 0; i < nAnimations; ++i)
        animationsArray.emplace_back(
            new Sprite(files[i], frameCount[i], frameTime[i]));
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
    // Resets all the animations when the state changes
    if (currentState != state) {
        currentState = state;
        for (int i = 0; i < nAnimations; i++) {
            animationsArray[i].get()->SetFrame(0);
        }
    }
}

int AnimationFSM::GetCurrentState(void)
{
    return currentState;
}

void AnimationFSM::SetNAnimations(int nAnimations)
{
    this->nAnimations = nAnimations;
}

int AnimationFSM::GetCurrentFrame(void)
{
    return animationsArray[currentState]->GetCurrentFrame();
}

void AnimationFSM::SetAnimation(unsigned long index, std::string file,
                                int frameCount, float frameTime, int rows)
{
    if (index >= animationsArray.size()) {
        nAnimations = index + 1;
        animationsArray.emplace(animationsArray.begin() + index, new Sprite());
    }

    animationsArray[index].get()->SetFrameCount(frameCount);
    animationsArray[index].get()->SetFrameTime(frameTime);
    animationsArray[index].get()->SetRows(rows);
    animationsArray[index].get()->Open(file);
}

int AnimationFSM::GetCurrentWidth(void)
{
    return animationsArray[currentState]->GetWidth();
}

int AnimationFSM::GetCurrentHeight(void)
{
    return animationsArray[currentState]->GetHeight();
}

