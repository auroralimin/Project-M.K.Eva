#include "Game.h"
#include "ProceduralState.h"
#include "IntroState.h"
#include "HubState.h"
#include "Vec2.h"
#include "ProceduralFirstRooms.h"
#include "Config.h"

int main(int argc, char **argv)
{
    if (argc < 2) {
        std::cerr << "You must specify the initial state" << std::endl;
        exit(EXIT_SUCCESS);
    }

    int variants[2] = {5, 4};
    for (int i = 1; i <= PROCEDURAL_GENERATED_SET; ++i)
        ProceduralFirstRooms::GenerateRooms(variants, i);

    if (std::string(argv[1]) == "intro") {
        Game *game = Game::GetInstance("Project M.K.Eva", SCREEN_W + SCREEN_PADDING, SCREEN_H + SCREEN_PADDING);
        game->Push(new IntroState(Vec2(SCREEN_W / 2, SCREEN_H / 2)));
        game->Run();
        delete game;
    } else if (std::string(argv[1]) == "procedural") {
        // Game *game = Game::GetInstance("Project M.K.Eva", 1280, 960);
        Game *game = Game::GetInstance("Project M.K.Eva", 448, 320);
        game->Push(new ProceduralState());
        game->Run();
        delete game;
    } else if (std::string(argv[1]) == "hub") {
        Game *game = Game::GetInstance("Project M.K.Eva", SCREEN_W, SCREEN_H);
        game->Push(new HubState());
        game->Run();
        delete game;
    } else {
        std::cerr << "Invalid State" << std::endl;
    }

    return 0;
}

