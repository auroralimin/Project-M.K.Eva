#include "IntroState.h"
#include "Camera.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Eva.h"
#include "Config.h"
#include "Game.h"
#include "Collision.h"
#include "Timer.h"
#include "HubState.h"
#include "Item.h"
#include "BallsManager.h"

IntroState::IntroState(Vec2 evaPos) : map(), music("music/introMusic.ogg"),
    evaDead(false)
{
    Eva *eva = new Eva(evaPos, false);
    AddObject(eva);
    map.SetFocus(eva);
    map.SetDrawMiniroom(true);
    map.Load("intro", "map/intro.txt");
    AddObject(new Item("SamuraiCard", Vec2(1000, 400)));
    AddObject(new Item("DeckerCard", Vec2(800, 400)));
    AddObject(new Item("GunnerCard", Vec2(900, 400)));
    map.SetFocus(eva);
    music.Play(-1);
}

IntroState::~IntroState()
{
    music.Stop();
}

void IntroState::Update(float dt)
{
    InputManager input = InputManager::GetInstance();
    quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());
    map.Update(dt);
    UpdateArray(dt);
    CheckMovementCollisions();
}

void IntroState::Render(void)
{
    map.Render();
    RenderArray();
    map.RenderMinimap();
}

void IntroState::Pause(void)
{
    // do nothing
}

void IntroState::Resume(void)
{
    // do nothing
}

bool IntroState::IsCollidingWithWall(GameObject *o)
{
    return map.IsCollidingWithWall(o);
}

void IntroState::UpdateArray(float dt)
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
            } if (objectArray[i]->Is("BallMonster")) {
                for (int j = 0; j < objectArray.size(); j++)
                    if (objectArray[j]->Is("BallsManager"))
                        ((BallsManager *) objectArray[j].get())->ClearDeadBalls();
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

void IntroState::CheckMovementCollisions()
{
    for (size_t i = 0; i < objectArray.size(); i++) {
        for (size_t j = i + 1; j < objectArray.size(); j++) {
            if (!(objectArray[i]->Is("Bullet")        ||
                  objectArray[j]->Is("Bullet")        || 
                  objectArray[i]->Is("BallMonster")   ||
                  objectArray[j]->Is("BallMonster")   ||
                  objectArray[i]->Is("Attack")        ||
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
                if (Collision::IsColliding(
                        objectArray[i]->attackHitbox, objectArray[j]->attackHitbox,
                        objectArray[i]->rotation, objectArray[j]->rotation)) {

                    objectArray[i]->NotifyCollision(*objectArray[j].get(),
                                                    true);
                    objectArray[j]->NotifyCollision(*objectArray[i].get(),
                                                    true);
                }
            }
        }
    }
}

void IntroState::UpdateEva(int i)
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

