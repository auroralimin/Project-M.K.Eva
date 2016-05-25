#include "AnimationFSM.h"

#define N_ANIMATIONS 5

AnimationFSM::AnimationFSM()
{
	for (int i = 0; i < N_ANIMATIONS; ++i)
		animationsArray.emplace_back(new Sprite());
    currentState = IDLE;
}

AnimationFSM::AnimationFSM(std::string files[], int frameCount, float frameTime)
{
	for (int i = 0; i < N_ANIMATIONS; ++i)
		animationsArray.emplace_back(new Sprite(files[i], frameCount, frameTime));
    currentState = IDLE;
}

void AnimationFSM::Render(int x, int y)
{
	animationsArray[currentState].get()->Render(x, y);
}

void AnimationFSM::Update(float dt)
{
	animationsArray[currentState].get()->Update(dt);
}

void AnimationFSM::SetCurrentState(AnimationFSM::AnimationState state)
{
    //Resets all the animations when the state changes
    if (currentState != state) {
        currentState = state;
		for (int i = 0; i < N_ANIMATIONS; ++i)
			animationsArray[i].get()->SetFrame(0);
    }
}

AnimationFSM::AnimationState AnimationFSM::GetCurrentState()
{
    return currentState;
}

void AnimationFSM::SetAnimation(int index, std::string file, int frameCount,
                                    float frameTime)
{
    animationsArray[index].get()->Open(file);
    animationsArray[index].get()->SetFrameCount(frameCount);
    animationsArray[index].get()->SetFrameTime(frameTime);
}

int AnimationFSM::GetSpriteWidth()
{
    return animationsArray[0].get()->GetWidth();
}

int AnimationFSM::GetSpriteHeight()
{
    return animationsArray[0].get()->GetHeight();
}

