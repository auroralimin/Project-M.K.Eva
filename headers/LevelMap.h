#pragma once
#include <vector>
#include <unordered_map>
#include <memory>

#include "Room.h"
#include "Vec2.h"
#include "Rect.h"
#include "GameObject.h"

/***************************************************************************/ /**
  * Level map abstraction.
  ******************************************************************************/
class LevelMap
{
  public:
    /**
     * Default initialisation
     */
    LevelMap(void);

    /**
     * Initialises Level map by loading it attributes value from a giver map
     * file.
     * @param file a string with the map file path
     */
    LevelMap(std::string name, std::string file, GameObject *focus);

    /**
     * Loads map attributes values from a giver map file.
     * @param file a string with the map file path
     */
    void Load(std::string name, std::string file);

    void SetFocus(GameObject *focus);

    void Update(float dt);

    /**
     * Renders the current map room.
     */
    void Render(void);

    /**
     * Renders the minimap
     */
    void RenderMinimap(void);

    /**
     * Sets the current map room.
     */
    void SetCurrentRoom(Vec2 room);

    /**
     * Checks if room is out of limits.
     * @param room a Vec2 with the room to be checked coordinates
     * @return If it is out of limits
     */
    bool IsOutOfLimits(Vec2 room);

    /**
     * Set current map room to be the room on top of the current one.
     */
    void RoomUp(void);

    /**
     * Set current map room to be the room on bottom of the current one.
     */
    void RoomDown(void);

    /**
     * Set current map room to be the room on left of the current one.
     */
    void RoomLeft(void);

    /**
     * Set current map room to be the room on right of the current one.
     */
    void RoomRight(void);

    /**
     * Get current room.
     * @return Returns current room vector of coordinates.
     */
    Vec2 GetCurrentRoom(void);

    /**
     * Get map width.
     * @return Returns map width
     */
    int GetWidth(void);

    /**
     * Get map height.
     * @return Returns map height
     */
    int GetHeight(void);

    /**
     * Checks if a given object is colliding with the current room walls.
     * @param obj a game object with the object to be checked
     * @return Returns if the collision occured
     */
    bool IsCollidingWithWall(GameObject *obj);

    void NotifyDeadMonster(void);

    void SetDrawMiniroom(bool drawMiniroom);

  private:
    GameObject *focus;
    bool drawMiniroom;
    std::string name; 
    int mapWidth, mapHeight, index;
    Vec2 currentRoom;
    std::unordered_map<int, Room *> rooms;
    Rect miniRoom, miniRoom2;
};

