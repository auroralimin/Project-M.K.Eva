#include "TitleState.h"
#include "StageState.h"
#include "Game.h"
#include "InputManager.h"

#define UNUSED_VAR (void)

TitleState::TitleState(void) : bg("img/title.jpg") {}

void TitleState::Update(float dt)
{
	UNUSED_VAR dt;
	InputManager input = InputManager::GetInstance(); 

	if (input.KeyPress(ESCAPE_KEY) || input.IsQuitRequested())
		popRequested = true;
	if (input.KeyPress(SPACEBAR))
		Game::GetInstance()->Push(new StageState());
}

void TitleState::Render(void)
{
	bg.Render(0, 0);
}

void TitleState::Pause(void)
{
	//do nothing
}

void TitleState::Resume(void)
{
	//do nothing
}

