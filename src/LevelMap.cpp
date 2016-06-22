#include <iostream>

#include "LevelMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "Rect.h"
#include "Config.h"
#include "Collision.h"

#define MINI_ROOM_SIZE_X 30
#define MINI_ROOM_SIZE_Y 22
#define MINI_ROOM_BORDER 3
#define MINIMAP_X 1000
#define MINIMAP_Y 0

LevelMap::LevelMap(void)
{
}

LevelMap::LevelMap(std::string file, GameObject *focus) : focus(focus)
{
    Load(file);
    InitMiniroom();
}

void LevelMap::Load(std::string file)
{
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

    int r;
    while (fscanf(fp, "%d,", &r) != EOF) {
        if (r != -1 && rooms.find(r) == rooms.end())
            rooms.emplace(
                r, new Room(roomsPath + std::to_string(r) + ".txt",
                    tileSet, focus, 1));
        mapMatrix.emplace_back(r);
    }
    index = mapMatrix[currentRoom.x + (mapWidth * currentRoom.y)];

    fclose(fp);
}

void LevelMap::InitMiniroom(void)
{
    miniRoom.dim.x = MINI_ROOM_SIZE_X * mapWidth + MINI_ROOM_BORDER * 2;
    miniRoom.dim.y = MINI_ROOM_SIZE_Y * mapHeight + MINI_ROOM_BORDER * 2;
    miniRoom.pos.x = MINIMAP_X - MINI_ROOM_BORDER;
    miniRoom.pos.y = MINIMAP_Y - MINI_ROOM_BORDER;

    miniRoom2.dim.x = MINI_ROOM_SIZE_X - MINI_ROOM_BORDER * 2;
    miniRoom2.dim.y = MINI_ROOM_SIZE_Y - MINI_ROOM_BORDER * 2;
}

void LevelMap::SetFocus(GameObject *focus)
{
    this->focus = focus;
}

void LevelMap::Update(float dt)
{
    rooms[index]->Update(dt);
}

void LevelMap::Render(void)
{
    rooms[index]->Render(Camera::pos.x, Camera::pos.y);

    int color1[4] = COLOR_T_GREY_1;
    miniRoom.RenderFilledRect(color1);

    int color2[4] = COLOR_T_GREY_2;
    int color3[4] = COLOR_T_GREY_3;
    for (int i = 0; i < mapWidth; i++) {
        for (int j = 0; j < mapHeight; j++) {
            if (!IsOutOfLimits(Vec2(i, j)) &&
                (mapMatrix[i + mapWidth * j] > -1)) {
                miniRoom2.pos.x =
                    i * MINI_ROOM_SIZE_X + MINIMAP_X + MINI_ROOM_BORDER;
                miniRoom2.pos.y =
                    j * MINI_ROOM_SIZE_Y + MINIMAP_Y + MINI_ROOM_BORDER;
                if (!(currentRoom.x == i && currentRoom.y == j))
                    miniRoom2.RenderFilledRect(color2);
                else
                    miniRoom2.RenderFilledRect(color3);
            }
        }
    }
}

void LevelMap::SetCurrentRoom(Vec2 room)
{
    if (!IsOutOfLimits(room)) {
        currentRoom = room;
        index = mapMatrix[currentRoom.x + (mapWidth * currentRoom.y)];
    } else
        std::cout << "Reached map out of limits" << std::endl;
}

bool LevelMap::IsOutOfLimits(Vec2 room)
{
    if (room.x < 0 || room.y < 0)
        return true;

    int newIndex = mapMatrix[room.x + (mapWidth * room.y)];
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

