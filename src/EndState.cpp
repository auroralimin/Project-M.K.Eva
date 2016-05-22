#include "EndState.h"
#include "TitleState.h"
#include "StageState.h"
#include "Game.h"
#include "InputManager.h"

EndState::EndState(StateData data) : bg(), music(),
	text1("font/Call me maybe.ttf", 70, Text::TextStyle::BLENDED,
			"     Press space to to try again",
			{255, 255, 255, 255}),
	text2("font/Call me maybe.ttf", 70, Text::TextStyle::BLENDED,
			"  Or press ESC to return to menu",
			{255, 255, 255, 255}, 0, 80)
{
	if (data.playerVictory)
	{
		bg.Open("img/win.jpg");
		music.Open("audio/endStateWin.ogg");
	}
	else
	{
		bg.Open("img/lose.jpg");
		music.Open("audio/endStateLose.ogg");
	}
}

void EndState::Update(float dt)
{
	InputManager input = InputManager::GetInstance(); 

	if (input.IsQuitRequested())
		quitRequested = true;
	if (input.KeyPress(ESCAPE_KEY))
	{
		Game::GetInstance()->Push(new TitleState());
		popRequested = true;
	}
	if (input.KeyPress(SPACEBAR))
	{
		Game::GetInstance()->Push(new StageState());
		popRequested = true;
	}
	
	timer.Update(dt);
}

void EndState::Render(void)
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
	{
		text1.Render();
		text2.Render();
	}
}

void EndState::Pause(void)
{
	//do nothing
}

void EndState::Resume(void)
{
	//do nothing
}

