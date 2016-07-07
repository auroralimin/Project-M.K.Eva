#pragma once

#include <vector>

#include "TileMap.h"
#include "Door.h"
#include "GameObject.h"

class Room
{
  public:
    Room(std::string level, int id, std::string file, TileSet *tileSet,
            GameObject *focus, int type);
    void Update(float dt);
    void Render(int cameraX = 0, int cameraY = 0);
    std::vector<Rect> GetWallRect(void);
    void DecreaseNMonsters(void);
    bool WasVisited(void);
    void SetIsFirst(bool isFirst);
    void SetIsNeighbour(bool isNeighbour);
    bool GetIsNeighbour(void);
    int GetId(void);

  private:
    enum roomState {INACTIVE, ACTIVE, DISABLED};

    std::string level;
    TileMap tileMap;
    GameObject *focus;
    int id, type, nMonsters;
    roomState currentState;
    bool isNeighbour, isFirst;
    Door doors[4];
    std::vector<Rect> wallRect;

    void SetDoors(void);
    void LoadWallRects(void);
    void ActivateRoom(void);
};

