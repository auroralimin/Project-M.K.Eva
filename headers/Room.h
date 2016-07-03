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
    void DecreaseNMonsters(void);
    bool WasVisited(void);
    void SetIsNeighbour(bool isNeighbour);
    bool GetIsNeighbour(void);

  private:
    enum roomState {INACTIVE, ACTIVE, DISABLED};
    TileMap tileMap;
    GameObject *focus;
    int type, nMonsters;
    roomState currentState;
    bool isNeighbour;
    bool hasDoors[4] = {false, false, false, false};
    std::vector<Rect> wallRect;

    void SetDoors(std::string file);
    void LoadWallRects(void);
    void ActivateRoom(void);
};

