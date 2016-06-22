#include <cmath>

#include "Room.h"
#include "Config.h"

Room::Room(std::string file, TileSet *tileSet) : tileMap(file, tileSet)
{
    SetDoors(file);
    LoadWallRects();
}

void Room::Render(int cameraX, int cameraY)
{
    tileMap.Render(cameraX, cameraY);

    int color[4] = COLOR_HITBOX;
    if (Config::HITBOX_MODE)
        for (auto hitbox : wallRect)
            hitbox.RenderFilledRect(color);
}

std::vector<Rect> Room::GetWallRect(void)
{
    return wallRect;
}

void Room::SetDoors(std::string file)
{
#ifdef WINDOWS
    std::string delim = "\\";
#else
    std::string delim = "/";
#endif
    int start = file.rfind(delim);
    int end = file.find('.', start);
    int fileId = atoi(file.substr(start + 1, end - 1).c_str());

    for (int i = 4; i > 0; --i)
        if (fileId >= pow(10, i)) {
            hasDoors[4 - i] = true;
            fileId -= pow(10, i);
        }
}

void Room::LoadWallRects(void)
{
    // clang-format off
    static int posWidth1[4]  = {             0, -TILE_SIZE * 2,                    0, SCREEN_W - TILE_SIZE},
               posHeight1[4] = {-TILE_SIZE * 2,  TILE_SIZE * 3, SCREEN_H - TILE_SIZE,        TILE_SIZE * 3},
               dimWidth1[4]  = { TILE_SIZE * 9,  TILE_SIZE * 3,        TILE_SIZE * 9,        TILE_SIZE * 3},
               dimHeight1[4] = { TILE_SIZE * 5,  TILE_SIZE * 3,        TILE_SIZE * 3,        TILE_SIZE * 3},
               posWidth2[4]  = {TILE_SIZE * 11, -TILE_SIZE * 2,       TILE_SIZE * 11, SCREEN_W - TILE_SIZE},
               posHeight2[4] = {-TILE_SIZE * 2,  TILE_SIZE * 7, SCREEN_H - TILE_SIZE,        TILE_SIZE * 7},
               dimWidth2[4]  = {TILE_SIZE * 20,  TILE_SIZE * 3,       TILE_SIZE * 20,            TILE_SIZE},
               dimHeight2[4] = { TILE_SIZE * 5,  TILE_SIZE * 7,        TILE_SIZE * 3,        TILE_SIZE * 7};
    // clang-format on

    for (int i = 0; i < 4; ++i)
        if (hasDoors[i]) {
            wallRect.emplace_back(Vec2(posWidtposHeight1[i], h1[i]),
                                  Vec2(dimWidth1[i], dimHeight1[i]));
            wallRect.emplace_back(Vec2(posWidth2[i], posHeight2[i]),
                                  Vec2(dimWidth1[i], dimHeight1[i]));
        } else {
            wallRect.emplace_back(Vec2(posWidth1[i], h1[i]),
                                  Vec2(dimWidth2[i], dimHeighth2[i]));
        }
}

