#include <ctime>
#include <iomanip>
#include <fstream>

#include "SDL2/SDL.h"
#include "Game.h"
#include "Config.h"
#include "ProceduralMap.h"

#define ROOM_SIZE 64
#define S_PATH "img/green_map/"
#define D_PATH "img/red_map/"
#define FR_PATH "img/blue_map/"

int **ProceduralMap::map = nullptr;
int ProceduralMap::totalRooms = 0;
int ProceduralMap::width = 0;
int ProceduralMap::height = 0;
int ProceduralMap::nMaps = 0;
bool ProceduralMap::render = false;
Vec2 ProceduralMap::firstRoom(0, 0);
ProceduralMap::MapConfig ProceduralMap::config;
std::string ProceduralMap::path;

std::string ProceduralMap::GenerateMap(int width, int height, int totalRooms,
                                       MapConfig config, bool render)
{
    ProceduralMap::width = width;
    ProceduralMap::height = height;
    ProceduralMap::totalRooms = totalRooms;
    ProceduralMap::render = render;
    ProceduralMap::config = config;
    path = (config == MapConfig::SPARSE) ? S_PATH : D_PATH;
    nMaps++;

    float p = (width * height) / totalRooms;
    if (p < 0.8 || width < 3 || height < 3) {
        std::cerr << "Inconsistent map arguments" << std::endl;
        return nullptr;
    }

    SetupMap();

    Automaton((int)(p * 1.5 * config), 1, 4);
    LabelRooms();
    if (render)
        Render(false, path);
    std::string file = GenerateMapFile();

    DeleteMap();

    return file;
}

void ProceduralMap::SetupMap(void)
{
    map = new int *[width];
    for (int i = 0; i < width; ++i) {
        map[i] = new int[height];
        std::fill_n(map[i], height, -1);
    }

    int x, y;
    x = 1 + std::rand() % (width - 2);
    y = 1 + std::rand() % (height - 2);
    map[x][y] = 1;
    map[x - 1][y] = map[x + 1][y] = map[x][y - 1] = map[x][y + 1] = 0;
    firstRoom.x = x;
    firstRoom.y = y;
}

void ProceduralMap::Automaton(int minRoomPerGen, int nRooms, int nPossibilities)
{
    static int gen = 0;
    int newRooms = 0;
    float probability;

    for (int j = 0; j < height; ++j)
        for (int i = 0; i < width; ++i)
            if (map[i][j] == 0) {
                probability =
                    ((float)(minRoomPerGen)-newRooms) / nPossibilities;
                if (CellReprodution(i, j, probability))
                    newRooms++;
                nPossibilities--;
            }

    nPossibilities += NewPossibilities();
    nRooms += newRooms;
    if (totalRooms - nRooms < minRoomPerGen)
        minRoomPerGen = totalRooms - nRooms;

    gen++;
    if (render)
        Render(true, path);
    if (totalRooms != nRooms)
        Automaton(minRoomPerGen, nRooms, nPossibilities);

    if (Config::DEBUG && gen != 0)
        std::cout << "Number of generations: " << gen << std::endl
                  << std::endl;
    gen = 0;
}

bool ProceduralMap::CellReprodution(const int x, const int y,
                                    const float probability)
{
    int neighbors = 0;

    if ((x < 0) || ((x > 0) && (map[x - 1][y] == 1)))
        neighbors++;
    if ((x >= width) || ((x < width - 1) && (map[x + 1][y] == 1)))
        neighbors++;
    if ((y < 0) || ((y > 0) && (map[x][y - 1] == 1)))
        neighbors++;
    if ((y >= height) || ((y < height - 1) && (map[x][y + 1] == 1)))
        neighbors++;

    if (!(x == firstRoom.x - 1 && y == firstRoom.y) &&
        neighbors < (1 + config) &&
        (float)(rand() % 99) < (probability * 100)) {
        map[x][y] = 1;
        return true;
    }

    map[x][y] = -1;
    return false;
}

void ProceduralMap::Render(const bool renderGeneration, const std::string path)
{
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            if (map[i][j] > 0) {
                std::string roomFile = std::to_string(map[i][j]) + ".png";
                if (i == firstRoom.x && j == firstRoom.y)
                    Sprite(FR_PATH + roomFile)
                        .Render(i * ROOM_SIZE, j * ROOM_SIZE);
                else
                    Sprite(path + roomFile)
                        .Render(i * ROOM_SIZE, j * ROOM_SIZE);
            }

    if (renderGeneration) {
        SDL_Delay(250);
        SDL_RenderPresent(Game::GetInstance()->GetRenderer());
    }
}

int ProceduralMap::NewPossibilities(void)
{
    int n = 0;

    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j)
            if ((map[i][j] == -1) && ((i > 0 && map[i - 1][j] == 1) ||
                                      (i < width - 1 && map[i + 1][j] == 1) ||
                                      (j > 0 && map[i][j - 1] == 1) ||
                                      (j < height - 1 && map[i][j + 1] == 1))) {
                n++;
                map[i][j] = 0;
            }

    return n;
}

void ProceduralMap::LabelRooms(void)
{
    int roomId = 0;
    for (int i = 0; i < width; ++i)
        for (int j = 0; j < height; ++j) {
            if (map[i][j] > 0) {
                if ((j < height - 1) && (map[i][j + 1] > 0))
                    roomId += 10;
                if ((j > 0) && (map[i][j - 1] > 0))
                    roomId += 100;
                if ((i > 0) && (map[i - 1][j] > 0))
                    roomId += 1000;
                if ((i < width - 1) && (map[i + 1][j] > 0))
                    roomId += 10000;
                if ((i == firstRoom.x) && (j == firstRoom.y))
                    roomId += 1000;
                map[i][j] = roomId;
                roomId = 0;
            } else if (map[i][j] == 0)
                map[i][j] = -1;
        }
}

std::string ProceduralMap::GenerateMapFile(void)
{
    std::string file =
        "map/procedural_generated_map" + std::to_string(nMaps) + ".txt";
    std::ofstream out;

    out.open(file);
    if (!out) {
        std::cerr << "Failed to write on file: " << file << std::endl;
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(EXIT_SUCCESS);
    }

    out << "tileset/lab.png" << std::endl
        << std::endl;
    out << "tilemap/procedural_generated_1/" << std::endl
        << std::endl;

    out << width << "," << height << std::endl;
    out << firstRoom.x << "," << firstRoom.y << std::endl
        << std::endl;

    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i)
            out << map[i][j] << ",";
        out << std::endl;
    }

    out.close();
    return file;
}

void ProceduralMap::DeleteMap(void)
{
    for (int i = 0; i < width; ++i)
        delete map[i];

    delete map;
    map = nullptr;
}

void ProceduralMap::PrintMap(void)
{
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i)
            std::cout << std::setw(6) << map[i][j] << ",";
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

