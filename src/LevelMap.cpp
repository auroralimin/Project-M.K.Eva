#include <iostream>

#include "LevelMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "Rect.h"
#include "Config.h"
#include "Collision.h"

#define VISITED_PATH "img/default_map/"
#define IMG1 "img/unvisited_map.png"
#define IMG2 "img/current_map.png"
#define MINI_ROOM_SIZE_X 40
#define MINI_ROOM_SIZE_Y 22
#define MINI_ROOM_BORDER 2
#define MINIMAP_X 1000
#define MINIMAP_Y 20

LevelMap::LevelMap(void) : focus(nullptr), drawMinimap(false), type(0)
{
}

LevelMap::LevelMap(std::string name, std::string file, GameObject *focus,
                   int type)
    : focus(focus), drawMinimap(false), type(type)
{
    Load(name, file);
}

void LevelMap::Load(std::string name, std::string file)
{
    this->name = name;
    FILE *fp = fopen(file.c_str(), "r");

    if (!fp) {
        std::cerr << "Failed to open file: " << file << std::endl;
        exit(EXIT_SUCCESS);
    }

    char tileSetFile[100];
    fscanf(fp, "%s\n\n", tileSetFile);
    TileSet *tileSet =
        new TileSet(TILE_SIZE, TILE_SIZE, std::string(tileSetFile));

    char roomsPath[200];
    fscanf(fp, "%s\n", roomsPath);

    fscanf(fp, "%d,%d,", &mapWidth, &mapHeight);
    fscanf(fp, "%f,%f,", &currentRoom.x, &currentRoom.y);

    int r, n = 0;
    while (fscanf(fp, "%d,", &r) != EOF) {
        if (r != -1) {
            switch (type) {
            case 1: {
                if (r == 110) {
                    rooms.emplace(
                        n++, new Room(name, r,
                                      roomsPath + std::to_string(r) + ".txt",
                                      tileSet, focus, 999));
                } else if (r == 11000) {
                    rooms.emplace(
                        n++, new Room(name, r,
                                      roomsPath + std::to_string(r) + ".txt",
                                      tileSet, focus, 1));
                } else if (r == 1010) {
                    rooms.emplace(
                        n++, new Room(name, r,
                                      roomsPath + std::to_string(r) + ".txt",
                                      tileSet, focus, 2));
                } else {
                    rooms.emplace(
                        n++, new Room(name, r,
                                      roomsPath + std::to_string(r) + ".txt",
                                      tileSet, focus, 3));
                }
                break;
            }
            case 2: {
                 rooms.emplace(n++, new Room(name, r,
                             roomsPath + std::to_string(r) + ".txt",
                             tileSet, focus, 999));
                 break;
            }
            default: {
                rooms.emplace(n++,
                              new Room(name, r,
                                       roomsPath + std::to_string(r) + ".txt",
                                       tileSet, focus, Config::Rand(5, 9)));
            }
            }
        } else {
            rooms.emplace(n++, nullptr);
        }
    }
    index = currentRoom.x + (mapWidth * currentRoom.y);
    rooms[index]->SetIsFirst(true);

    fclose(fp);
}

void LevelMap::SetFocus(GameObject *focus)
{
    this->focus = focus;
}

void LevelMap::Update(float dt)
{
    if (focus != nullptr)
        rooms[index]->Update(dt);
}

void LevelMap::Render(void)
{
    rooms[index]->Render(Camera::pos.x, Camera::pos.y);
}

void LevelMap::RenderMinimap(void)
{
    if (!drawMinimap)
        return;

    int color1[4] = COLOR_T_GREY_1;
    miniRoom.RenderFilledRect(color1);

    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            int roomId = i + mapWidth * j;
            if (!IsOutOfLimits(Vec2(i, j)) && rooms[roomId] != nullptr) {
                int x = i * MINI_ROOM_SIZE_X + MINIMAP_X - MINI_ROOM_BORDER * i;
                int y = j * MINI_ROOM_SIZE_Y + MINIMAP_Y - MINI_ROOM_BORDER * j;
                if (currentRoom.x == i && currentRoom.y == j) {
                    Sprite(VISITED_PATH +
                           std::to_string(rooms[roomId]->GetId()) +
                           ".png").Render(x, y);
                    Sprite(IMG2).Render(x, y);
                } else if (rooms[roomId]->WasVisited()) {
                    Sprite(VISITED_PATH +
                           std::to_string(rooms[roomId]->GetId()) +
                           ".png").Render(x, y);
                } else if (rooms[roomId]->GetIsNeighbour() ||
                           (currentRoom.x == i && (currentRoom.y == j + 1 ||
                                                   currentRoom.y == j - 1)) ||
                           (currentRoom.y == j && (currentRoom.x == i + 1 ||
                                                   currentRoom.x == i - 1))) {
                    Sprite(VISITED_PATH +
                           std::to_string(rooms[roomId]->GetId()) +
                           ".png").Render(x, y);
                    Sprite(IMG1).Render(x, y);
                    rooms[roomId]->SetIsNeighbour(true);
                }
            }
        }
    }
}

void LevelMap::SetCurrentRoom(Vec2 room)
{
    if (!IsOutOfLimits(room)) {
        currentRoom = room;
        index = currentRoom.x + (mapWidth * currentRoom.y);
    } else
        std::cout << "Reached map out of limits" << std::endl;
}

bool LevelMap::IsOutOfLimits(Vec2 room)
{
    if (room.x < 0 || room.y < 0)
        return true;

    int newIndex = room.x + (mapWidth * room.y);
    return ((room.x >= mapWidth) || (room.y >= mapHeight) || newIndex == -1);
}

void LevelMap::RoomUp(void)
{
    Vec2 v = Vec2(currentRoom.x, currentRoom.y - 1);
    SetCurrentRoom(v);
}

void LevelMap::RoomDown(void)
{
    Vec2 v = Vec2(currentRoom.x, currentRoom.y + 1);
    SetCurrentRoom(v);
}

void LevelMap::RoomLeft(void)
{
    Vec2 v = Vec2(currentRoom.x - 1, currentRoom.y);
    SetCurrentRoom(v);
}

void LevelMap::RoomRight(void)
{
    Vec2 v = Vec2(currentRoom.x + 1, currentRoom.y);
    SetCurrentRoom(v);
}

Vec2 LevelMap::GetCurrentRoom(void)
{
    return currentRoom;
}

int LevelMap::GetWidth(void)
{
    return mapWidth;
}

int LevelMap::GetHeight(void)
{
    return mapHeight;
}

bool LevelMap::IsCollidingWithWall(GameObject *obj)
{
    std::vector<Rect> wallRect = rooms[index]->GetWallRect();
    for (size_t i = 0; i < wallRect.size(); i++)
        if (Collision::IsColliding(obj->hitbox, wallRect[i], obj->rotation, 0))
            return true;

    return false;
}

void LevelMap::NotifyDeadMonster(void)
{
    rooms[index]->DecreaseNMonsters();
}

void LevelMap::SetDrawMiniroom(bool drawMinimap)
{
    this->drawMinimap = drawMinimap;
}

void LevelMap::SetType(int type)
{
    this->type = type;
}

