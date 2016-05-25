#include "Game.h"
#include "IntroState.h"

#define UNUSED_VAR (void)

int main(int argc, char **argv)
{
	UNUSED_VAR argc;
	UNUSED_VAR argv;

	Game *game = Game::GetInstance("Project M.K.Eva", 1280, 704);
	game->Push(new IntroState());
	game->Run();
	delete game;

	return 0;
}

