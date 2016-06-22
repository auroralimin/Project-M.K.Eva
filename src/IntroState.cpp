#include "IntroState.h"
#include "Camera.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Eva.h"
#include "Turret.h"
#include "MekaBug.h"
#include "TurretMob.h"
#include "MonsterBallManager.h"
#include "Config.h"
#include "Game.h"
#include "Collision.h"
#include "Timer.h"

IntroState::IntroState(Vec2 evaPos) : map()
{
    Camera::pos = Vec2(0.0, 0.0);
    Eva *eva = new Eva(evaPos);
    AddObject(eva);
    //	AddObject(new Turret(Vec2(Game::GetInstance()->GetWinWidth()/2 + 50,
    //                    Game::GetInstance()->GetWinHeight()/2), eva));
    //	AddObject(new MekaBug(Vec2(Game::GetInstance()->GetWinWidth()/2 + 100,
    //                    Game::GetInstance()->GetWinHeight()/2 + 100), eva));
    //	AddObject(new MekaBug(Vec2(Game::GetInstance()->GetWinWidth()/2 - 100,
    //                    Game::GetInstance()->GetWinHeight()/2 - 100), eva));
    //	AddObject(new TurretMob(Vec2(Game::GetInstance()->GetWinWidth()/2 - 200,
    //                    Game::GetInstance()->GetWinHeight()/2 - 200), eva));
    //	AddObject(new TurretMob(Vec2(Game::GetInstance()->GetWinWidth()/3,
    //                    Game::GetInstance()->GetWinHeight()/2), eva));
    //	AddObject(new TurretMob(Vec2(Game::GetInstance()->GetWinWidth()/2,
    //                    Game::GetInstance()->GetWinHeight()/3), eva));
    MonsterBallManager *ballManager = new MonsterBallManager(eva);
    AddObject(ballManager);
    for (int i = 0; i < 5; ++i)
        AddObject(*(ballManager->AddBall()));
    map.Load("map/intro.txt");
    map.InitMiniroom();
    map.SetFocus(eva);
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
    Rect bg(Vec2(-SCREEN_PADDING/2, -SCREEN_PADDING/2),
            Vec2(SCREEN_W + 2*SCREEN_PADDING, SCREEN_H + 2*SCREEN_PADDING));
    int color[4] = COLOR_BLACK;
    bg.RenderFilledRect(color);
    map.Render();
    RenderArray();
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
            if (objectArray[i]->Is("Eva"))
                evaDeath = ((Eva *)(objectArray[i].get()))->GetEvaDeath();
            else if (objectArray[i]->Is(evaDeath))
                popRequested = quitRequested = true;
            objectArray.erase(objectArray.begin() + i);
        } else {
            if (objectArray[i]->Is("Eva"))
                UpdateEva(i);
            objectArray[i]->Update((float)(dt / 1000));
        }
    }
}

void IntroState::CheckMovementCollisions()
{
    for (size_t i = 0; i < objectArray.size(); i++) {
        for (size_t j = i + 1; j < objectArray.size(); j++) {
            if (!(objectArray[i]->Is("Bullet") ||
                  (objectArray[j]->Is("Bullet")))) {
                if (Collision::IsColliding(
                        objectArray[i]->hitbox, objectArray[j]->hitbox,
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

