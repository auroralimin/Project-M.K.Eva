#include "HubState.h"
#include "Config.h"
#include "Camera.h"
#include "Game.h"
#include "Eva.h"
#include "InputManager.h"
#include "IntroState.h"
#include "FirstLevelState.h"
#include "Animation.h"

#define EVA_DRAWER_POSITION_X 130
#define EVA_DRAWER_POSITION_Y 100

HubState::HubState(void) : map(), music("music/hubMusic.ogg")
{
    map.Load("hub", "map/hub.txt");
    AddObject(new Animation(Vec2(EVA_DRAWER_POSITION_X, EVA_DRAWER_POSITION_Y),
                            0, "sprites/eva/drawer/DRAWER-EVA.png",
                            48, 0.08, true, 3));
    music.Play(-1);
}

HubState::~HubState(void)
{
    music.Stop();
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
    // do nothing
}

void HubState::Resume(void)
{
    //    music.Play(-1);
    //    AddObject(new Animation(Vec2(EVA_DRAWER_POSITION_X, EVA_DRAWER_POSITION_Y),
    //                            0, "sprites/eva/drawer/DRAWER-EVA.png",
    //                            48, 0.08, true, 3));
    //    for (unsigned int i = 0; i < objectArray.size(); i++) {
    //        if (objectArray[i]->Is("Eva"))
    //            objectArray.erase(objectArray.begin() + i);
    //
}

bool HubState::IsCollidingWithWall(GameObject *o)
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
            objectArray[i]->Update((float)(dt / 1000));
        }
    }
}

void HubState::UpdateEva(int i)
{
    int roomWidth = Game::GetInstance()->GetWinWidth();
    int roomHeight = Game::GetInstance()->GetWinHeight();

    if (objectArray[i]->box.pos.x + objectArray[i]->box.dim.x < 0) {
        Game *game = Game::GetInstance();
        game->Push(new IntroState(Vec2(roomWidth, objectArray[i]->box.pos.y)));
        popRequested = quitRequested = true;
        objectArray[i]->box.pos.x = Game::GetInstance()->GetWinWidth() / 2;
        objectArray[i]->box.pos.y = Game::GetInstance()->GetWinHeight() / 2;
    } else if (objectArray[i]->box.pos.x > roomWidth) {
        Game *game = Game::GetInstance();
        game->Push(new FirstLevelState(
            Vec2(-objectArray[i]->box.dim.x, objectArray[i]->box.pos.y)));
        popRequested = quitRequested = true;
        objectArray[i]->box.pos.x = Game::GetInstance()->GetWinWidth() / 2;
        objectArray[i]->box.pos.y = Game::GetInstance()->GetWinHeight() / 2;
    } else if (objectArray[i]->box.pos.y + objectArray[i]->box.dim.y < 0) {
        map.RoomUp();
        objectArray[i]->box.pos.y = roomHeight;
    } else if (objectArray[i]->box.pos.y >= roomHeight) {
        map.RoomDown();
        objectArray[i]->box.pos.y = 0 - objectArray[i]->box.dim.y;
    }
}

void HubState::CheckMovementCollisions()
{
}

