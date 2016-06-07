#include <ctime>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <sys/stat.h>

#include "ProceduralFirstRooms.h"

#define ROOM_WIDTH 20
#define ROOM_HEIGHT 11

int ProceduralFirstRooms::variants[2] = {0, 0};
int** ProceduralFirstRooms::floor = nullptr;
int** ProceduralFirstRooms::walls = nullptr;
int** ProceduralFirstRooms::details = nullptr;
std::string ProceduralFirstRooms::path = "";
std::string ProceduralFirstRooms::floorModules[5] = {
            "ULC.txt", "URC.txt", "LLC.txt", "LRC.txt", "CENTER.txt"};
std::string ProceduralFirstRooms::wallsModules[4] = {
           "DOWN.txt", "UP.txt", "LEFT.txt", "RIGHT.txt"};
std::string ProceduralFirstRooms::detailsModules[6] = {
           "LWLC.txt", "LWCENTER.txt", "LWRC.txt",
           "RWLC.txt", "RWCENTER.txt", "RWRC.txt"};

void ProceduralFirstRooms::GenerateRooms(int variants[2], int pathId)
{
    ProceduralFirstRooms::variants[0] = variants[0];
    ProceduralFirstRooms::variants[1] = variants[1];
    std::srand(std::time(0));
    
    path = "tilemap/procedural_generated_" + std::to_string(pathId) + "/";
    #ifdef WINDOWS
        mkdir(path.c_str());
    #else
        mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    #endif

    for (int d = 0; d < 2; ++d)
        for (int u = 0; u < 2; ++u)
            for (int l = 0; l < 2; ++l)
                for (int r = 0; r < 2; ++r)
                    GenerateRoom(d*10 + u*100 + l*1000 + r*10000);
}

void ProceduralFirstRooms::GenerateRoom(int roomId)
{
    SetLayers();
    GenerateRoomFloor();
    GenerateRoomWalls(roomId);
    bool hasDetails = GenerateRoomDetails();
    WriteRoom(roomId, hasDetails);
}

void ProceduralFirstRooms::SetLayers(void)
{
    floor = new int*[ROOM_HEIGHT];
    walls = new int*[ROOM_HEIGHT];
    details = new int*[ROOM_HEIGHT];

    for (int i = 0; i < ROOM_HEIGHT; ++i)
    {
        floor[i] = new int[ROOM_WIDTH];
        walls[i] = new int[ROOM_WIDTH];
        details[i] = new int[ROOM_WIDTH];
        std::fill_n(floor[i], ROOM_WIDTH, -1);
        std::fill_n(walls[i], ROOM_WIDTH, -1);
        std::fill_n(details[i], ROOM_WIDTH, -1);
    }
}

void ProceduralFirstRooms::GenerateRoomFloor(void)
{
    int random;
    LoadModule("modules/fixed/floor/BASE.txt", &floor);
    random = 1 + std::rand() % variants[0];
    for (int i = 0; i < 5; ++i) {
        LoadModule("modules/" + std::to_string(random) +
            "/floor/" + floorModules[i], &floor);
    }
}

void ProceduralFirstRooms::GenerateRoomWalls(int roomId)
{
    int j = 0;
        
    for (int i = 4; i > 0; i--) {
        j = pow(10, i);
        if (roomId >= j) {
            LoadModule("modules/fixed/wall/doored/" + wallsModules[i-1], &walls);
            roomId -= j;
        } else {
            LoadModule("modules/fixed/wall/doorless/" + wallsModules[i-1], &walls);
        }
    }
}

bool ProceduralFirstRooms::GenerateRoomDetails(void)
{
    int prob, random;
    bool hasDetails = false;

    for (int i = 0; i < 6; i++) {
        prob = std::rand() % 100;
        if (prob > 75) {
            random = 1 + std::rand() % variants[1];
            LoadModule("modules/" + std::to_string(random) +
                    "/details/" + detailsModules[i], &details);
            hasDetails = true;
        }
    }

    return hasDetails;
}

void ProceduralFirstRooms::LoadModule(std::string file, int ***layer)
{
    FILE *fp;
    int tile;

    fp = fopen(file.c_str(), "r");
    if (!fp)
    {
        std::cerr << "Failed to open file: " <<  file << std::endl;
        exit(EXIT_SUCCESS);	
    }
    for (int i = 0; i < ROOM_HEIGHT; ++i) {
        for (int j = 0; j < ROOM_WIDTH; ++j) {
            fscanf(fp, "%d,", &tile);
            if (tile != -1)
                (*layer)[i][j] = tile;
        }
    }
    fclose(fp);
}

void ProceduralFirstRooms::WriteRoom(int roomId, bool hasDetails)
{
	std::string file = path + std::to_string(roomId) + ".txt";
	std::ofstream out;

    out.open(file.c_str());
    if (!out)
    {
        std::cerr << "Failed to write on file: " << file << std::endl;
        std::cerr << "Error: " << strerror(errno) << std::endl;
        exit(EXIT_SUCCESS);	
    }

    if (hasDetails)
        out << "20,11,3," << std::endl << std::endl;
    else
        out << "20,11,2," << std::endl << std::endl;  

    for (int i = 0; i < ROOM_HEIGHT; ++i) {
        for (int j = 0; j < ROOM_WIDTH; ++j) {
            out << std::to_string(floor[i][j]) << ",";
        }
        out << std::endl;
    }
    out << std::endl;

    for (int i = 0; i < ROOM_HEIGHT; ++i) {
        for (int j = 0; j < ROOM_WIDTH; ++j) {
            out << std::to_string(walls[i][j]) << ",";
        }
        out << std::endl;
    }
    out << std::endl;

    if (hasDetails) {
        for (int i = 0; i < ROOM_HEIGHT; ++i) {
            for (int j = 0; j < ROOM_WIDTH; ++j) {
                out << std::to_string(details[i][j]) << ",";
            }
            out << std::endl;
        }
        out << std::endl;
    }

    out.close();
}

