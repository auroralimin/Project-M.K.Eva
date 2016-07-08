#include "TitleState.h"
#include "HubState.h"
#include "Game.h"
#include "Config.h"
#include "InputManager.h"

TitleState::TitleState(void) :
    cutscene(Vec2(0, 0), "begin", 70, 0.1, "soundeffect/begin.wav"),
    titleFadeIn(Vec2(0, 0), "title", 14, 0.1),
    title("img/title.png"), msg("img/msg.png"), timer()
{
    titleFadeIn.SetPos(Vec2((SCREEN_W - title.GetWidth()) / 2,
                (SCREEN_H - title.GetHeight()) / 2));
} 

void TitleState::Update(float dt)
{
	InputManager input = InputManager::GetInstance(); 

    if (!cutscene.IsDead())
        cutscene.Update(dt);
    else if (!titleFadeIn.IsDead())
        titleFadeIn.Update(dt);
    else
    	timer.Update(dt);

	if (input.KeyPress(SPACEBAR))
	{
        if (!cutscene.IsDead()) {
            cutscene.Kill();
        } else if (titleFadeIn.IsDead()) {
            titleFadeIn.Kill();
	    	Game *game = Game::GetInstance();
            game->Push(new HubState());
	    	popRequested = quitRequested = true;
        }
	}
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

