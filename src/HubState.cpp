#include "HubState.h"
#include "Config.h"
#include "Camera.h"
#include "Game.h"
#include "Eva.h"
#include "InputManager.h"
#include "IntroState.h"
#include "FirstLevelState.h"

HubState::HubState(void) : map()
{
    map.Load("map/hub.txt");
    Camera::pos = Vec2(0.0, 0.0);
    AddObject(new Eva(Vec2(Game::GetInstance()->GetWinWidth()/2,
                    Game::GetInstance()->GetWinHeight()/2)));
}

void HubState::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());
    UpdateArray(dt);
}

void HubState::Render(void)
{
    map.Render();
    RenderArray();
}

void HubState::Pause(void)
{

}

void HubState::Resume(void)
{

}

bool HubState::IsCollidingWithWall(GameObject* o)
{
    return map.IsCollidingWithWall(o);
}

void HubState::UpdateArray(float dt)
{
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        } else {
            if (objectArray[i]->Is("Eva"))
                UpdateEva(i);
            objectArray[i]->Update((float)(dt/1000));
        }
    }
}

void HubState::UpdateEva(int i)
{
    int roomWidth = Game::GetInstance()->GetWinWidth();
    int roomHeight = Game::GetInstance()->GetWinHeight();

    if (objectArray[i]->box.pos.x + objectArray[i]->box.dim.x < 0) {
        Game *game = Game::GetInstance();
        Pause();
        game->Push(new IntroState(Vec2(roomWidth, objectArray[i]->box.pos.y)));
    } else if (objectArray[i]->box.pos.x > roomWidth) {
        Game *game = Game::GetInstance();
        Pause();
        game->Push(new FirstLevelState(Vec2(-objectArray[i]->box.dim.x,
                        objectArray[i]->box.pos.y)));
    } else if (objectArray[i]->box.pos.y + objectArray[i]->box.dim.y < 0) {
        map.RoomUp();
        objectArray[i]->box.pos.y = roomHeight;
    } else if (objectArray[i]->box.pos.y >= roomHeight) {
        map.RoomDown();
        objectArray[i]->box.pos.y = 0 - objectArray[i]->box.dim.y;
    }
}

void HubState::CheckMovementCollisions() {}
