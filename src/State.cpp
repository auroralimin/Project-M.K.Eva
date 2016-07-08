#include <iostream>
#include <algorithm>

#include "State.h"

State::State(void) : popRequested(false), quitRequested(false)
{
}

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
        objectArray[i]->Update((float)(dt / 1000));
}

bool WayToSort(std::unique_ptr<GameObject> const& obj1,
        std::unique_ptr<GameObject> const& obj2)
{
    return (obj1->hitbox.pos.y < obj2->hitbox.pos.y);
}

void State::RenderArray(void)
{
    sort(objectArray.begin(), objectArray.end(), WayToSort);

    for (unsigned int i = 0; i < objectArray.size(); ++i)
        objectArray[i]->Render();
}


