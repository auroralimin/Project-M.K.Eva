#include <cmath>

#include "Room.h"
#include "Game.h"
#include "Config.h"
#include "TurretMonster.h"
#include "MekaBugMonster.h"
#include "TurretMobMonster.h"
#include "BallsManager.h"

Room::Room(std::string level, int id, std::string file, TileSet *tileSet,
        GameObject *focus, int type) :
    level(level), tileMap(file, tileSet), focus(focus), id(id), type(type),
    nMonsters(0), currentState(roomState::INACTIVE), isNeighbour(false),
    isFirst(false)
{
    SetDoors();
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
        for (int i = 0; i < 4; ++i)
            if (doors[i].GetCurrentState() == Door::DoorState::OPENED) {
                if (level == "procedural_generated_1" && i == 1 && isFirst)
                    doors[1].SetCurrentState(Door::DoorState::WALL);
                else if (level == "intro" && i == 3 && isFirst)
                    doors[3].SetCurrentState(Door::DoorState::WALL);
                else
                    doors[i].SetCurrentState(Door::DoorState::CLOSED);
            }
        ActivateRoom();
    } else if ((currentState == roomState::ACTIVE) && nMonsters <= 0) {
        currentState = roomState::DISABLED;
        for (int i = 0; i < 4; ++i)
            if (doors[i].GetCurrentState() == Door::DoorState::CLOSED)
                doors[i].SetCurrentState(Door::DoorState::OPENED);
    }

    LoadWallRects();
    for (int i = 0; i < 4; ++i)
        doors[i].Update(dt);
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

    for (int i = 0; i < 4; ++i)
        doors[i].Render();
}

std::vector<Rect> Room::GetWallRect(void)
{
    return wallRect;
}

void Room::SetDoors(void)
{
    int fileId = id;
    std::string directionStr[4] = {"up/", "left/", "down/", "right/"};
   
    for (int i = 4; i > 0; --i)
        if (fileId >= pow(10, i)) {
            std::string direction = directionStr[4 - i];
            doors[4 - i].Load(4 - i, Door::DoorState::OPENED,
                    "sprites/door/" + level + "/" + direction); 
            fileId -= pow(10, i);
        }
}

void Room::LoadWallRects(void)
{
    wallRect.clear();

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
        if (doors[i].GetCurrentState() == Door::DoorState::OPENED) {
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
            Game::GetInstance()->GetCurrentState().AddObject(new TurretMonster(
                        this, Vec2(Game::GetInstance()->GetWinWidth()/2 + 50,
                            Game::GetInstance()->GetWinHeight()/2), focus));
            nMonsters++;
            break;
            }
        case 2:
            {
            Game::GetInstance()->GetCurrentState().AddObject(
                    new MekaBugMonster(this,
                        Vec2(Game::GetInstance()->GetWinWidth()/2 + 100,
                            Game::GetInstance()->GetWinHeight()/2 + 100),
                        focus));
            Game::GetInstance()->GetCurrentState().AddObject(
                    new MekaBugMonster(this,
                        Vec2(Game::GetInstance()->GetWinWidth()/2 - 100,
                            Game::GetInstance()->GetWinHeight()/2 - 100),
                        focus));
            nMonsters += 2;
            break;
            }
        case 3:
            {
            BallsManager *ballManager = new BallsManager(this, focus);
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
            Game::GetInstance()->GetCurrentState().AddObject(
                    new TurretMobMonster(this,
                        Vec2(Game::GetInstance()->GetWinWidth()/2 - 200,
                            Game::GetInstance()->GetWinHeight()/2 - 200),
                        focus));
            Game::GetInstance()->GetCurrentState().AddObject(
                    new TurretMobMonster(this,
                        Vec2(Game::GetInstance()->GetWinWidth()/3,
                            Game::GetInstance()->GetWinHeight()/2), focus));
            Game::GetInstance()->GetCurrentState().AddObject(
                    new TurretMobMonster(this,
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

bool Room::WasVisited(void)
{
   return (currentState == roomState::DISABLED);
}

void Room::SetIsFirst(bool isFirst)
{
    this->isFirst = isFirst;
}

void Room::SetIsNeighbour(bool isNeighbour)
{
    this->isNeighbour = isNeighbour;
}

bool Room::GetIsNeighbour(void)
{
    return isNeighbour;
}

int Room::GetId(void)
{
    return id;
}

