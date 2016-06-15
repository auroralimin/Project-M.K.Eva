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

IntroState::IntroState(void) : map("map/procedural_generated_map1.txt")
{
	Camera::pos = Vec2(0.0, 0.0);
	AddObject(new Turret(Vec2(Game::GetInstance()->GetWinWidth()/2 + 50, Game::GetInstance()->GetWinHeight()/2)));
	AddObject(new MekaBug(Vec2(Game::GetInstance()->GetWinWidth()/2 + 100, Game::GetInstance()->GetWinHeight()/2 + 100)));
	AddObject(new MekaBug(Vec2(Game::GetInstance()->GetWinWidth()/2 - 100, Game::GetInstance()->GetWinHeight()/2 - 100)));
	AddObject(new TurretMob(Vec2(Game::GetInstance()->GetWinWidth()/2 - 200, Game::GetInstance()->GetWinHeight()/2 - 200)));
	AddObject(new TurretMob(Vec2(Game::GetInstance()->GetWinWidth()/3, Game::GetInstance()->GetWinHeight()/2)));
	AddObject(new TurretMob(Vec2(Game::GetInstance()->GetWinWidth()/2, Game::GetInstance()->GetWinHeight()/3)));
	AddObject(new MonsterBallManager(5));
    AddObject(new Eva(Vec2(Game::GetInstance()->GetWinWidth()/2,
                           Game::GetInstance()->GetWinHeight()/2)));
}

void IntroState::Update(float dt)
{
	UNUSED_VAR dt;
	InputManager input = InputManager::GetInstance();
    int roomWidth = Game::GetInstance()->GetWinWidth();
    int roomHeight = Game::GetInstance()->GetWinHeight();

    quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());

    if (Eva::player) {
        if (Eva::player->box.pos.x + Eva::player->box.dim.x < 0){
            map.RoomLeft();
            Eva::player->box.pos.x = roomWidth;
        } else if (Eva::player->box.pos.x > roomWidth){
            map.RoomRight();
            Eva::player->box.pos.x = 0 - Eva::player->box.dim.x;
        } else if (Eva::player->box.pos.y + Eva::player->box.dim.y < 0){
            map.RoomUp();
            Eva::player->box.pos.y = roomHeight;
        } else if (Eva::player->box.pos.y >= roomHeight){
            map.RoomDown();
            Eva::player->box.pos.y = 0 - Eva::player->box.dim.y;
        }
    }
    UpdateArray(dt);
	CheckMovementCollisions();
}

void IntroState::Render(void)
{
	map.Render();
	RenderArray();
}

void IntroState::Pause(void)
{
	//do nothing
}

void IntroState::Resume(void)
{
	//do nothing
}

bool IntroState::IsCollidingWithWall(GameObject* o)
{
    return map.IsCollidingWithWall(o);
}

void IntroState::UpdateArray(float dt)
{
    for (unsigned int i = 0; i < objectArray.size(); i++) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin() + i);
        } else {
            objectArray[i]->Update((float)(dt/1000));
        }
    }
}

void IntroState::CheckMovementCollisions()
{
	for (size_t i = 0; i < objectArray.size(); i++) {
		for (size_t j = i+1;j < objectArray.size(); j++) {
			if (!(objectArray[i]->Is("Bullet") || (objectArray[j]->Is("Bullet")))) {
				if (Collision::IsColliding(objectArray[i]->hitbox, objectArray[j]->hitbox, 
					objectArray[i]->rotation, objectArray[j]->rotation)) {

					objectArray[i]->NotifyCollision(*objectArray[j].get(), true);
					objectArray[j]->NotifyCollision(*objectArray[i].get(), true);
				}
			}
		}
	}
}
