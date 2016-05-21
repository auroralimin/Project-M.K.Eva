#include "State.h"

State::State(void) : popRequested(false), quitRequested(false) {}

void State::AddObject(GameObject *obj)
{
	objectArray.emplace_back(obj);
}

bool State::IsPopRequested(void)
{
	return popRequested;
}

bool State::IsQuitRequested(void)
{
	return quitRequested;
}

void State::UpdateArray(float dt)
{
	for (unsigned int i = 0; i < objectArray.size(); ++i)
		objectArray[i]->Update((float)(dt/1000));
}

void State::RenderArray(void)
{
	for (unsigned int i = 0; i < objectArray.size(); ++i)
		objectArray[i]->Render();
}

