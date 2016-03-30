#include "Game.h"

#define UNUSED_VAR (void)

int main(int argc, char **argv)
{
	UNUSED_VAR argc;
	UNUSED_VAR argv;

	Game *game = Game::getInstance("Aurora Wang - 13/0006408", 1024, 600);
	game->run();

	return 0;
}

