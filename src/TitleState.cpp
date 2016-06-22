#include "TitleState.h"
#include "HubState.h"
#include "Game.h"
#include "Config.h"
#include "InputManager.h"

TitleState::TitleState(void) :
    title("img/title.png"), msg("img/msg.png"), timer() {} 

void TitleState::Update(float dt)
{
	InputManager input = InputManager::GetInstance(); 

	if (input.KeyPress(ESCAPE_KEY) || input.IsQuitRequested())
		popRequested = true;
	if (input.KeyPress(SPACEBAR))
	{
		Game::GetInstance()->Push(new HubState());
		popRequested = true;
	}
	
	timer.Update(dt);
}

void TitleState::Render(void)
{
	static bool print = true;

	title.Render((SCREEN_W - title.GetWidth()) / 2,
            (SCREEN_H - title.GetHeight()) / 2);

	if (timer.Get() > 700)
	{
		print = !print;
        timer.Restart();
	}
	if (print)
        msg.Render((SCREEN_W - msg.GetWidth()) / 2,
                (SCREEN_H + title.GetHeight()) / 2 - 35);
}

void TitleState::Pause(void)
{
	//do nothing
}

void TitleState::Resume(void)
{
	//do nothing
}

bool TitleState::IsCollidingWithWall(GameObject *obj)
{
    UNUSED_VAR obj;
	//do nothing
    return false;
}

void TitleState::CheckMovementCollisions(void)
{
	//do nothing
}

