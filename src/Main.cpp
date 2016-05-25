#include "Game.h"
#include "ProceduralState.h"
#include "IntroState.h"

#define UNUSED_VAR (void)

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		std::cerr << "You must specify the initial state" << std::endl;
		exit(EXIT_SUCCESS);
	}

	if (std::string(argv[1]) == "intro")
	{
		Game *game = Game::GetInstance("Project M.K.Eva", 1280, 704);
		game->Push(new IntroState());
		game->Run();
		delete game;
	}
	else if (std::string(argv[1]) == "procedural")
	{
		Game *game = Game::GetInstance("Project M.K.Eva", 1920, 1080);
		game->Push(new ProceduralState());
		game->Run();
		delete game;
	}

	return 0;
}

