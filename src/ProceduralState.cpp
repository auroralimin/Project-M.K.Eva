#include "ProceduralState.h"
#include "ProceduralMap.h"
#include "Camera.h"
#include "Vec2.h"
#include "InputManager.h"

#define UNUSED_VAR (void)

ProceduralState::ProceduralState(void)
{
	Camera::pos = Vec2(0.0, 0.0);
	ProceduralMap::GenerateMap(5, 5, 10, ProceduralMap::MapConfig::RANDOM);
}

void ProceduralState::Update(float dt)
{
	UNUSED_VAR dt;
	InputManager input = InputManager::GetInstance();

	quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());
}

void ProceduralState::Render(void)
{
	//do nothing
}

void ProceduralState::Pause(void)
{
	//do nothing
}

void ProceduralState::Resume(void)
{
	//do nothing
}

bool ProceduralState::IsCollidingWithWall(GameObject* obj)
{
	UNUSED_VAR obj;
	//do nothing
	return false;
}

