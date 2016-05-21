#include "Game.h"
#include "TitleState.h"

#define UNUSED_VAR (void)

int main(int argc, char **argv)
{
	UNUSED_VAR argc;
	UNUSED_VAR argv;

	Game *game = Game::GetInstance("Aurora Wang - 13/0006408", 1024, 600);
	game->Push(new TitleState());
	game->Run();
	delete game;

	return 0;
}

