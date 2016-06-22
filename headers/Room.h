#pragma once

#include <vector>

#include "TileMap.h"
#include "GameObject.h"

class Room
{
  public:
    Room(std::string file, TileSet *tileSet, GameObject *focus, int type);
    void Update(float dt);
    void Render(int cameraX = 0, int cameraY = 0);
    std::vector<Rect> GetWallRect(void);

  private:
    enum roomState {INACTIVE, ACTIVE, DISABLED};
    TileMap tileMap;
    GameObject *focus;
    roomState currentState;
    bool hasDoors[4] = {false, false, false};
    std::vector<Rect> wallRect;

    void SetDoors(std::string file);
    void LoadWallRects(void);
};

