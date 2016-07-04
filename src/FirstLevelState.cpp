#include <ctime>

#include "FirstLevelState.h"
#include "Camera.h"
#include "ProceduralMap.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Eva.h"
#include "Config.h"
#include "Game.h"

FirstLevelState::FirstLevelState(Vec2 evaPos) : map(), isEvaDead(false), music("music/introMusic.ogg")
{
    seed = std::time(0);
    if (Config::DEBUG)
        std::cout << "seed: " << seed << std::endl;
    std::srand(seed);
    std::string mapString = ProceduralMap::GenerateMap(
        7, 5, 15, ProceduralMap::MapConfig::SPARSE, false);

    Eva *eva = new Eva(evaPos);
    AddObject(eva);
    map.SetFocus(eva);
    map.Load(mapString);
    map.InitMiniroom();
    music.Play(-1);
}

void FirstLevelState::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());
    UpdateArray(dt);
}

void FirstLevelState::Render(void)
{
    map.Render();
    RenderArray();
}

void FirstLevelState::Pause(void)
{
    // do nothing
}

void FirstLevelState::Resume(void)
{
    // do nothing
}

bool FirstLevelState::IsCollidingWithWall(GameObject *o)
{
    return map.IsCollidingWithWall(o);
}

void FirstLevelState::UpdateArray(float dt)
{
    static std::string evaDeath = "";
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            if (objectArray[i]->Is("Eva")) {
                evaDeath = ((Eva *)(objectArray[i].get()))->GetEvaDeath();
                isEvaDead = true;
            }
            if (isEvaDead && objectArray[i]->Is(evaDeath))
                popRequested = quitRequested = true;

            objectArray.erase(objectArray.begin() + i);
        } else {
            if (objectArray[i]->Is("Eva"))
                UpdateEva(i);
            objectArray[i]->Update((float)(dt / 1000));
        }
    }
}

void FirstLevelState::UpdateEva(int i)
{
    int roomWidth = Game::GetInstance()->GetWinWidth();
    int roomHeight = Game::GetInstance()->GetWinHeight();

    if (objectArray[i]->box.pos.x + objectArray[i]->box.dim.x < 0) {
        map.RoomLeft();
        objectArray[i]->box.pos.x = roomWidth;
    } else if (objectArray[i]->box.pos.x > roomWidth) {
        map.RoomRight();
        objectArray[i]->box.pos.x = 0 - objectArray[i]->box.dim.x;
    } else if (objectArray[i]->box.pos.y + objectArray[i]->box.dim.y < 0) {
        map.RoomUp();
        objectArray[i]->box.pos.y = roomHeight;
    } else if (objectArray[i]->box.pos.y >= roomHeight) {
        map.RoomDown();
        objectArray[i]->box.pos.y = 0 - objectArray[i]->box.dim.y;
    }
}

void FirstLevelState::CheckMovementCollisions()
{
}

