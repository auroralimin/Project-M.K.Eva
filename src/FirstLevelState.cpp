#include <ctime>

#include "FirstLevelState.h"
#include "Camera.h"
#include "ProceduralMap.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Eva.h"
#include "Config.h"
#include "Game.h"
#include "HubState.h"
#include "Collision.h"
#include "Boss.h"
#include "BallsManager.h"

FirstLevelState::FirstLevelState(Vec2 evaPos)
    : map(), music("music/introMusic.ogg"), evaDead(false)
{
    seed = std::time(0);
    if (Config::DEBUG)
        std::cout << "seed: " << seed << std::endl;
    std::srand(seed);
    std::string mapString = ProceduralMap::GenerateMap(
        7, 5, 15, ProceduralMap::MapConfig::SPARSE, false);

    Eva *eva = new Eva(evaPos, true);
    AddObject(eva);
    map.SetType(3);
    map.SetFocus(eva);
    map.SetDrawMiniroom(true);
    map.Load("procedural_generated_1", mapString);
    music.Play(-1);
}

FirstLevelState::~FirstLevelState()
{
    music.Stop();
}

void FirstLevelState::Update(float dt)
{
    map.Update(dt);
    InputManager input = InputManager::GetInstance();
    quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());
    UpdateArray(dt);
    CheckMovementCollisions();
}

void FirstLevelState::Render(void)
{
    map.Render();
    RenderArray();
    map.RenderMinimap();
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
                evaDead = true;
            } else if (objectArray[i]->Is("Turret") ||
                       objectArray[i]->Is("TurretMob") ||
                       objectArray[i]->Is("Mekabug")) {
                map.NotifyDeadMonster();
            } else if (objectArray[i]->Is(evaDeath)) {
                popRequested = quitRequested = true;
                Game *game = Game::GetInstance();
                game->Push(new HubState());
            }
            if (objectArray[i]->Is("BallMonster")) {
                for (unsigned long j = 0; j < objectArray.size(); j++)
                    if (objectArray[j]->Is("BallsManager"))
                        ((BallsManager *)objectArray[j].get())
                            ->ClearDeadBalls();
                objectArray[i] = nullptr;
            }

            objectArray.erase(objectArray.begin() + i);
        } else {
            if (objectArray[i]->Is("Eva"))
                UpdateEva(i);
            if (!(evaDead && objectArray[i]->Is("BallsManager")))
                objectArray[i]->Update((float)(dt / 1000));
        }
    }
}

void FirstLevelState::CheckMovementCollisions(void)
{
    for (size_t i = 0; i < objectArray.size(); i++) {
        for (size_t j = i + 1; j < objectArray.size(); j++) {
            if (!(objectArray[i]->Is("Bullet") ||
                  objectArray[j]->Is("Bullet") ||
                  objectArray[i]->Is("BallMonster") ||
                  objectArray[j]->Is("BallMonster") ||
                  objectArray[i]->Is("Attack") ||
                  objectArray[j]->Is("Attack"))) {
                if (Collision::IsColliding(
                        objectArray[i]->hitbox, objectArray[j]->hitbox,
                        objectArray[i]->rotation, objectArray[j]->rotation)) {

                    objectArray[i]->NotifyCollision(*objectArray[j].get(),
                                                    true);
                    objectArray[j]->NotifyCollision(*objectArray[i].get(),
                                                    true);
                }
            } else {
                if (Collision::IsColliding(objectArray[i]->attackHitbox,
                                           objectArray[j]->attackHitbox,
                                           objectArray[i]->rotation,
                                           objectArray[j]->rotation)) {

                    objectArray[i]->NotifyCollision(*objectArray[j].get(),
                                                    true);
                    objectArray[j]->NotifyCollision(*objectArray[i].get(),
                                                    true);
                }
            }
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

