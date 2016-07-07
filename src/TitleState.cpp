#include "TitleState.h"
#include "HubState.h"
#include "Game.h"
#include "Config.h"
#include "InputManager.h"

TitleState::TitleState(void) : cutscene(Vec2(0, 0), "begin", 25, 0.3),
    titleFadeIn(Vec2(0, 0), "title", 14, 0.15),
    title("img/title.png"), msg("img/msg.png"), timer()
{
    titleFadeIn.SetPos(Vec2((SCREEN_W - title.GetWidth()) / 2,
                (SCREEN_H - title.GetHeight()) / 2));
} 

void TitleState::Update(float dt)
{
	InputManager input = InputManager::GetInstance(); 

	if (input.KeyPress(ESCAPE_KEY) || input.IsQuitRequested())
		popRequested = true;
	if (input.KeyPress(SPACEBAR))
	{
        if (cutscene.IsDead()) {
	    	Game::GetInstance()->Push(new HubState());
	    	popRequested = true;
        } else {
            cutscene.Kill();
        }
	}

    if (!cutscene.IsDead())
        cutscene.Update(dt);
    else if (!titleFadeIn.IsDead())
        titleFadeIn.Update(dt);
    else
    	timer.Update(dt);
}

void TitleState::Render(void)
{
    if (!cutscene.IsDead()) {
        cutscene.Render();
    } else if (!titleFadeIn.IsDead()) {
        titleFadeIn.Render();
    } else {
        static bool print = false;

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

