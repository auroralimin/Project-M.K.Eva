#pragma once

#include <vector>

#include "TileMap.h"

class Room
{
  public:
    Room(std::string file, TileSet *tileSet);
    void Render(int cameraX = 0, int cameraY = 0);
    std::vector<Rect> GetWallRect(void);

  private:
    bool hasDoors[4] = {false, false, false, false};
    TileMap tileMap;
    std::vector<Rect> wallRect;

    void SetDoors(std::string file);
    void LoadWallRects(void);
};

