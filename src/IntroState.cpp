#include "IntroState.h"
#include "Camera.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Eva.h"

#define UNUSED_VAR (void)

IntroState::IntroState(void) : map("map/intro.txt")
{
	Camera::pos = Vec2(0.0, 0.0);
	std::string files[5] = {std::string("sprites/eva/movement/EVA-BASE-PARADA.png"),
		std::string("sprites/eva/movement/EVA-BASE-UP.png"),
		std::string("sprites/eva/movement/EVA-BASE-DOWN.png"),
		std::string("sprites/eva/movement/EVA-BASE-LEFT.png"),
		std::string("sprites/eva/movement/EVA-BASE-RIGHT.png")};
	AddObject(new Eva(Vec2(300, 150), files, 6, 0.08));
}

void IntroState::Update(float dt)
{
	UNUSED_VAR dt;
	InputManager input = InputManager::GetInstance();

	quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());
    if (Eva::player->box.pos.x + Eva::player->box.dim.x < 0){
        map.RoomLeft();
        Eva::player->box.pos.x = 640;
    } else if (Eva::player->box.pos.x > 640){
        map.RoomRight();
        Eva::player->box.pos.x = 0 - Eva::player->box.dim.x;
    } else if (Eva::player->box.pos.y + Eva::player->box.dim.y < 0){
        map.RoomUp();
        Eva::player->box.pos.y = 352;
    } else if (Eva::player->box.pos.y >= 352){
        map.RoomDown();
        Eva::player->box.pos.y = 0 - Eva::player->box.dim.y;
    }
    UpdateArray(dt);
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

