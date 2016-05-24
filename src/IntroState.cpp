#include "IntroState.h"
#include "Camera.h"
#include "Vec2.h"
#include "InputManager.h"

#define UNUSED_VAR (void)

IntroState::IntroState(void) : map("map/intro.txt")
{
	Camera::pos = Vec2(0.0, 0.0);
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
}

void IntroState::Render(void)
{
	map.Render();
}

void IntroState::Pause(void)
{
	//do nothing
}

void IntroState::Resume(void)
{
	//do nothing
}

