#include "TitleState.h"
#include "StageState.h"
#include "Game.h"
#include "InputManager.h"

TitleState::TitleState(void) : bg("img/title.jpg"), text("font/Call me maybe.ttf",
		70, Text::TextStyle::BLENDED, "Press Space to start", {255, 255, 255, 255},
		200, 450), timer() {} 

void TitleState::Update(float dt)
{
	InputManager input = InputManager::GetInstance(); 

	if (input.KeyPress(ESCAPE_KEY) || input.IsQuitRequested())
		popRequested = true;
	if (input.KeyPress(SPACEBAR))
	{
		Game::GetInstance()->Push(new StageState());
		popRequested = true;
	}
	
	timer.Update(dt);
}

void TitleState::Render(void)
{
	static bool print = true;
	static int oldTime = timer.Get();
	bg.Render();

	if (timer.Get() - oldTime > 750)
	{
		oldTime = timer.Get();
		print = !print;
	}
	if (print)
		text.Render();
}

void TitleState::Pause(void)
{
	//do nothing
}

void TitleState::Resume(void)
{
	//do nothing
}

