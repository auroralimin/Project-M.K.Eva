#pragma once

#include <vector>

#include "TileMap.h"
#include "Door.h"
#include "GameObject.h"

/**************************************************************************/ /**
  * A game room abstraction.
  *****************************************************************************/
class Room
{
  public:
    /**
     * Initialises a room given arguments.
     * @param level a string containing the level name
     * @param int an id containing the room identification
     * @param file a string with the room file
     * @param tileSet a pointer to a TileSet that will be used to create the
     * rooms
     */
    Room(std::string level, int id, std::string file, TileSet *tileSet,
         GameObject *focus, int type);

    /**
     * Updates a room based on its current state
     * @param dt time elapsed between th current and the last frame
     */
    void Update(float dt);

    /**
     * Renders a room and possibly its hitboxes
     * @param cameraX a int with the camera x position
     * @param cameraY a int with the camera y position
     */
    void Render(int cameraX = 0, int cameraY = 0);

    /**
     * Gets the wall rects.
     * @return returns the wall rect
     */
    std::vector<Rect> GetWallRect(void);

    /**
     * Decrease the number of monsters in the room.
     */
    void DecreaseNMonsters(void);

    /**
     * Checks if this rooms was visited.
     * @return returns if the room was visited
     */
    bool WasVisited(void);

    /**
     * Sets if this room is the first room of the map.
     * @param isFirst a bool that saves if this room is the first room
     */
    void SetIsFirst(bool isFirst);

    /**
     * Sets if this room is neighbour of a visited room.
     * @param isNeighbour a bool that saves if this room is neighbour
     */
    void SetIsNeighbour(bool isNeighbour);

    /**
     * Gets if this room is neighbour of a visited room.
     * @return returns if this room is neighbour of a visited room
     */
    bool GetIsNeighbour(void);

    /**
     * Gets this room Id.
     * @return returns this room's id
     */
    int GetId(void);

  private:
    enum roomState { INACTIVE, ACTIVE, DISABLED };

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

