#include "Door.h"
#include "Config.h"
#include "Game.h"
#include "Vec2.h"
#include "Camera.h"
#include "Animation.h"

#define TRANSITIONING_TIME 1.5f

Vec2 spritePos[4] = {{576, 0}, {0, 256}, {576, 640}, {1216, 256}};

Door::Door(void) : state(DoorState::INVISIBLE), timer(), isTransitioning(false)
{
}

void Door::Load(int direction, DoorState state, std::string path)
{
    this->state = state;
    this->direction = direction;
    this->path = path;
}

void Door::Update(float dt)
{
    if (isTransitioning)
        timer.Update(dt);

    if (timer.Get() / 1000.0f >= TRANSITIONING_TIME) {
        timer.Restart();
        isTransitioning = false;
    }
}

void Door::Render(void)
{
    int color[4] = COLOR_HITBOX;
    if (!isTransitioning) {
        if (state == DoorState::CLOSED) {
            sps[state].Render(spritePos[direction].x - Camera::pos.x,
                              spritePos[direction].y - Camera::pos.y);
            if (Config::HITBOX_MODE) {
                Vec2 dim = Vec2(sps[state].GetWidth(), sps[state].GetHeight());
                Rect hitbox = Rect(spritePos[direction], dim);
                hitbox.RenderFilledRect(color);
            }
        } else if (state == DoorState::WALL) {
            sps[state].Render(spritePos[direction].x - Camera::pos.x,
                              spritePos[direction].y - Camera::pos.y -
                                  TILE_SIZE);
            if (Config::HITBOX_MODE) {
                Vec2 dim = Vec2(sps[state].GetWidth(), sps[state].GetHeight());
                Rect hitbox = Rect(spritePos[direction] - Vec2(0, 64), dim);
                hitbox.RenderFilledRect(color);
            }
        }
    }
}

void Door::SetCurrentState(int state)
{
    if (this->state == DoorState::OPENED && state == DoorState::CLOSED) {
        sps[1].Open(path + "closed.png");
        isTransitioning = true;
        Game::GetInstance()->GetCurrentState().AddObject(
            new Animation(spritePos[direction], 0, path + "closing.png", 13,
                          TRANSITIONING_TIME / 13.0f));
    } else if (this->state == DoorState::CLOSED && state == DoorState::OPENED) {
        isTransitioning = true;
        Game::GetInstance()->GetCurrentState().AddObject(
            new Animation(spritePos[direction], 0, path + "opening.png", 13,
                          TRANSITIONING_TIME / 13.0f));

    } else if (this->state == DoorState::OPENED && state == DoorState::WALL) {
        sps[0] = Sprite(path + "wall.png");
        Game::GetInstance()->GetCurrentState().AddObject(
            new Animation(spritePos[direction] - Vec2(0, TILE_SIZE), 0,
                          path + "sealing.png", 9, TRANSITIONING_TIME / 9.0f));
    }

    this->state = state;
}

int Door::GetCurrentState(void)
{
    return state;
}

