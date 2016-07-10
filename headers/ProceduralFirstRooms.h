#pragma once
#include <iostream>

#include "Sprite.h"
#include "Vec2.h"

/***************************************************************************/ /**
  * Static module that can procedural generates maps for the first level.
  ******************************************************************************/
class ProceduralFirstRooms
{
  public:
    /**
     * Procedural generates the rooms for the first level.
     * @param variants an int vector containing the variants used to the
     * procedural generation
     * @param pathId the id of the procedural generated first rooms directory
     */
    static void GenerateRooms(int variants[2], int pathId);

  private:
    static int variants[2];
    static int **floor, **walls, **details;
    static std::string path;
    static std::string floorModules[5];
    static std::string wallsModules[4];
    static std::string detailsModules[6];

    static void GenerateRoom(int roomId);
    static void SetLayers(void);
    static void GenerateRoomFloor(void);
    static void GenerateRoomWalls(int roomId);
    static bool GenerateRoomDetails(void);
    static void LoadModule(std::string file, int ***layer);
    static void WriteRoom(int roomId, bool hasDetails);
};

