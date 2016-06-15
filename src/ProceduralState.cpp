#include <ctime>

#include "ProceduralState.h"
#include "ProceduralMap.h"
#include "Camera.h"
#include "Vec2.h"
#include "Game.h"
#include "InputManager.h"
#include "Config.h"

ProceduralState::ProceduralState(void)
{
	Camera::pos = Vec2(0.0, 0.0);
	seed = 1464152697;
	std::cout << "seed: " << seed << std::endl;
	std::srand(seed);
	ProceduralMap::GenerateMap(7, 5, 15, ProceduralMap::MapConfig::SPARSE, true);
	//ProceduralMap::GenerateMap(20, 15, 150, ProceduralMap::MapConfig::SPARSE);
}

void ProceduralState::Update(float dt)
{
	UNUSED_VAR dt;
	InputManager input = InputManager::GetInstance();

	quitRequested = (input.IsKeyDown(ESCAPE_KEY) || input.IsQuitRequested());
	if (input.KeyPress(UP_ARROW_KEY))
	{
		Game::GetInstance()->ClearRenderer();
		seed = std::time(0);
		std::cout << "seed: " << seed << std::endl;
		std::srand(seed);
		ProceduralMap::GenerateMap(7, 5, 15, ProceduralMap::MapConfig::SPARSE, true);
		//ProceduralMap::GenerateMap(20, 15, 150, ProceduralMap::MapConfig::SPARSE);
	}
	if (input.KeyPress(DOWN_ARROW_KEY))
	{
		Game::GetInstance()->ClearRenderer();
		seed = std::time(0);
		std::cout << "seed: " << seed << std::endl;
		std::srand(seed);
		ProceduralMap::GenerateMap(7, 5, 15, ProceduralMap::MapConfig::DENSE, true);
		//ProceduralMap::GenerateMap(20, 15, 150, ProceduralMap::MapConfig::DENSE);
	}

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

void ProceduralState::CheckMovementCollisions()
{
}
