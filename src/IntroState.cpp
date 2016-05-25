#include "IntroState.h"
#include "Camera.h"
#include "Vec2.h"
#include "InputManager.h"
#include "Eva.h"

#define UNUSED_VAR (void)

IntroState::IntroState(void) : map("map/intro.txt")
{
	Camera::pos = Vec2(0.0, 0.0);
    AddObject(new Eva(300, 150,
                      std::string("sprites/eva/movement/EVA-BASE-PARADA.png"),
                      std::string("sprites/eva/movement/EVA-BASE-UP.png"),
                      std::string("sprites/eva/movement/EVA-BASE-DOWN.png"),
                      std::string("sprites/eva/movement/EVA-BASE-LEFT.png"),
                      std::string("sprites/eva/movement/EVA-BASE-RIGHT.png"),
                      6, 0.08));
}

void IntroState::Update(float dt)
{
    UNUSED_VAR dt;
	InputManager input = InputManager::GetInstance();

	quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());
	if (input.KeyPress(LEFT_ARROW_KEY))
		map.RoomLeft();
	else if (input.KeyPress(RIGHT_ARROW_KEY))
		map.RoomRight();
	else if (input.KeyPress(UP_ARROW_KEY))
		map.RoomUp();
	else if (input.KeyPress(DOWN_ARROW_KEY))
		map.RoomDown();
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

bool IntroState::IsCollidingWithWall(GameObject* o)
{
	return map.IsCollidingWithWall(o);
}
