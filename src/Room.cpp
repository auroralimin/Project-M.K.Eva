#include <cmath>

#include "Room.h"
#include "Game.h"
#include "Config.h"
#include "Turret.h"
#include "MekaBug.h"
#include "TurretMob.h"
#include "MonsterBallManager.h"

Room::Room(std::string file, TileSet *tileSet, GameObject *focus, int type) :
    tileMap(file, tileSet), focus(focus), type(type), nMonsters(0),
    currentState(roomState::INACTIVE)
{
    SetDoors(file);
    LoadWallRects();
}

void Room::Update(float dt)
{
    UNUSED_VAR dt;

    if ((currentState == roomState::INACTIVE) &&
            (focus->box.pos.x < SCREEN_W - (TILE_SIZE + focus->box.dim.x)) &&
            (focus->box.pos.y < SCREEN_H - (TILE_SIZE + focus->box.dim.y)) && 
            (focus->box.pos.x > TILE_SIZE) &&
            (focus->box.pos.y > (TILE_SIZE*3)))
    {
        currentState = roomState::ACTIVE;
        ActivateRoom();
    } else if ((currentState == roomState::ACTIVE) && nMonsters <= 0) {
        currentState = roomState::DISABLED;
    }

}

void Room::Render(int cameraX, int cameraY)
{
    int bgColor[4] = COLOR_BLACK;
    Rect padding[4];

    padding[0] = Rect(Vec2(-SCREEN_PADDING/2, -SCREEN_PADDING/2),
                      Vec2(SCREEN_W + SCREEN_PADDING, SCREEN_PADDING/2));
    padding[1] = Rect(Vec2(-SCREEN_PADDING/2, SCREEN_H),
                      Vec2(SCREEN_W + SCREEN_PADDING, SCREEN_PADDING/2));
    padding[2] = Rect(Vec2(-SCREEN_PADDING/2, -SCREEN_PADDING/2),
                     Vec2(SCREEN_PADDING/2, SCREEN_H + SCREEN_PADDING));
    padding[3] = Rect(Vec2(SCREEN_W, -SCREEN_PADDING/2),
                      Vec2(SCREEN_PADDING/2, SCREEN_H + SCREEN_PADDING));

    for (int i = 0; i < 4; i++) {
        padding[i].RenderFilledRect(bgColor);
    }

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
    std::string delim = "/";
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
            wallRect.emplace_back(Vec2(posWidth1[i], posHeight1[i]),
                                  Vec2(dimWidth1[i], dimHeight1[i]));
            wallRect.emplace_back(Vec2(posWidth2[i], posHeight2[i]),
                                  Vec2(dimWidth1[i], dimHeight1[i]));
        } else {
            wallRect.emplace_back(Vec2(posWidth1[i], posHeight1[i]),
                    Vec2(dimWidth2[i], dimHeight2[i]));
        }
}

void Room::ActivateRoom(void)
{
    switch (type)
    {
        case 1:
            {
            Game::GetInstance()->GetCurrentState().AddObject(new Turret(
                        Vec2(Game::GetInstance()->GetWinWidth()/2 + 50,
                            Game::GetInstance()->GetWinHeight()/2), focus));
            nMonsters++;
            break;
            }
        case 2:
            {
            Game::GetInstance()->GetCurrentState().AddObject(new MekaBug(
                        Vec2(Game::GetInstance()->GetWinWidth()/2 + 100,
                            Game::GetInstance()->GetWinHeight()/2 + 100),
                        focus));
            Game::GetInstance()->GetCurrentState().AddObject(new MekaBug(
                        Vec2(Game::GetInstance()->GetWinWidth()/2 - 100,
                            Game::GetInstance()->GetWinHeight()/2 - 100),
                        focus));
            nMonsters += 2;
            break;
            }
        case 3:
            {
            MonsterBallManager *ballManager = new MonsterBallManager(focus);
            Game::GetInstance()->GetCurrentState().AddObject(ballManager);
            for (int i = 0; i < 5; ++i) {
                Game::GetInstance()->GetCurrentState().AddObject(
                        *(ballManager->AddBall()));
            }
            nMonsters += 5;
            break;
            }
        case 4:
            {
            Game::GetInstance()->GetCurrentState().AddObject(new TurretMob(
                        Vec2(Game::GetInstance()->GetWinWidth()/2 - 200,
                            Game::GetInstance()->GetWinHeight()/2 - 200),
                        focus));
            Game::GetInstance()->GetCurrentState().AddObject(new TurretMob(
                        Vec2(Game::GetInstance()->GetWinWidth()/3,
                            Game::GetInstance()->GetWinHeight()/2), focus));
            Game::GetInstance()->GetCurrentState().AddObject(new TurretMob(
                        Vec2(Game::GetInstance()->GetWinWidth()/2,
                            Game::GetInstance()->GetWinHeight()/3), focus));
            nMonsters += 3;
            break;
            }
        default:
            {
            //do nothing
            break;
            }
    }
}

void Room::DecreaseNMonsters(void)
{
    nMonsters--;
}

