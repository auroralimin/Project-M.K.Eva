#include "Eva.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"

#include <iostream>

Eva::Eva(): evaAnimations()
{
    this->box.pos = Vec2();
    this->box.dim = Vec2();
    this->rotation = 0;
    this->hp = 100; //temp value
    this->idleFile = std::string("");
    this->moveUpFile = std::string("");
    this->moveDownFile = std::string("");
    this->moveLeftFile = std::string("");
    this->moveRightFile = std::string("");
    this->frameCount = 1;
    this->frameTime = 1.0f;
    this->moveSpeed = 150;
}

Eva::Eva(int x, int y, std::string idleFile, std::string upFile,
         std::string downFile, std::string leftFile, std::string rightFile,
         int frameCount, float frameTime, int moveSpeed):
    evaAnimations(idleFile, upFile, downFile, leftFile, rightFile ,
                  frameCount, frameTime)
{
    this->box.pos = Vec2(x, y);
    this->box.dim = Vec2(evaAnimations.GetSpriteWidth()/frameCount,
                         evaAnimations.GetSpriteHeight());
    this->rotation = 0;
    this->hp = 100; //temp value
    this->idleFile = idleFile;
    this->moveUpFile = upFile;
    this->moveDownFile = downFile;
    this->moveLeftFile = leftFile;
    this->moveRightFile = rightFile;
    this->moveSpeed = moveSpeed; //temp value
}

Eva::~Eva()
{

}

void Eva::Render()
{
    evaAnimations.Render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y);
}

void Eva::Update(float dt)
{
	Vec2 previousPos = box.pos;
    evaAnimations.Update(dt);
    InputManager &manager = InputManager::GetInstance();
    if (manager.IsKeyDown(W_KEY)) {
        box.pos += Vec2(0, -moveSpeed*dt);
        if (manager.IsKeyDown(D_KEY)) {
            evaAnimations.SetCurrentState(AnimationFSM::MOVING_RIGHT);
            box.pos += Vec2(moveSpeed*dt, 0);
        } else if (manager.IsKeyDown(A_KEY)) {
            evaAnimations.SetCurrentState(AnimationFSM::MOVING_LEFT);
            box.pos += Vec2(-moveSpeed*dt, 0);
        } else {
            evaAnimations.SetCurrentState(AnimationFSM::MOVING_UP);
        }
    } else if(manager.IsKeyDown(S_KEY)) {
        box.pos += Vec2(0, moveSpeed*dt);
        if (manager.IsKeyDown(D_KEY)) {
            evaAnimations.SetCurrentState(AnimationFSM::MOVING_RIGHT);
            box.pos += Vec2(moveSpeed*dt, 0);
        } else if (manager.IsKeyDown(A_KEY)) {
            evaAnimations.SetCurrentState(AnimationFSM::MOVING_LEFT);
            box.pos += Vec2(-moveSpeed*dt, 0);
        } else {
            evaAnimations.SetCurrentState(AnimationFSM::MOVING_DOWN);
        }
    } else if (manager.IsKeyDown(D_KEY)) {
        evaAnimations.SetCurrentState(AnimationFSM::MOVING_RIGHT);
        box.pos += Vec2(moveSpeed*dt, 0);
    } else if (manager.IsKeyDown(A_KEY)) {
        evaAnimations.SetCurrentState(AnimationFSM::MOVING_LEFT);
        box.pos += Vec2(-moveSpeed*dt, 0);
    }
    if (!manager.IsKeyDown(W_KEY) && !manager.IsKeyDown(S_KEY)
            && !manager.IsKeyDown(D_KEY) && !manager.IsKeyDown(A_KEY)) {
        evaAnimations.SetCurrentState(AnimationFSM::IDLE);
    }
	
	if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
	{
		std::cout << "colliding" << std::endl;
		box.pos = previousPos;
	}
}

bool Eva::IsDead()
{
    return (hp <= 0);
}

void Eva::NotifyCollision(GameObject &other)
{
    //to be done
}

bool Eva::Is(std::string className)
{
    return (className == std::string("Eva"));
}

void Eva::TakeDamage(int dmg)
{
    hp -= dmg;
}

void Eva::SetIdleFile(std::string file)
{
    idleFile = file;
    evaAnimations.SetIdleAnimation(idleFile, frameCount, frameTime);
}

void Eva::SetMoveUpFile(std::string file)
{
    moveUpFile = file;
    evaAnimations.SetMoveUpAnimation(moveUpFile, frameCount, frameTime);
}

void Eva::SetMoveDownFile(std::string file)
{
    moveDownFile = file;
    evaAnimations.SetMoveDownAnimation(moveDownFile, frameCount, frameTime);
}

void Eva::SetMoveLeftFile(std::string file)
{
    moveLeftFile = file;
    evaAnimations.SetMoveLeftAnimation(moveLeftFile, frameCount, frameTime);
}

void Eva::SetMoveRightFile(std::string file)
{
    moveRightFile = file;
    evaAnimations.SetMoveRightAnimation(moveRightFile, frameCount, frameTime);
}

void Eva::SetFrameTime(float time)
{
    frameTime = time;
    evaAnimations.SetIdleAnimation(idleFile, frameCount, frameTime);
    evaAnimations.SetMoveUpAnimation(moveUpFile, frameCount, frameTime);
    evaAnimations.SetMoveDownAnimation(moveDownFile, frameCount, frameTime);
    evaAnimations.SetMoveLeftAnimation(moveLeftFile, frameCount, frameTime);
    evaAnimations.SetMoveRightAnimation(moveRightFile, frameCount, frameTime);
}

void Eva::SetFrameCount(int count)
{
    frameCount = count;
    evaAnimations.SetIdleAnimation(idleFile, frameCount, frameTime);
    evaAnimations.SetMoveUpAnimation(moveUpFile, frameCount, frameTime);
    evaAnimations.SetMoveDownAnimation(moveDownFile, frameCount, frameTime);
    evaAnimations.SetMoveLeftAnimation(moveLeftFile, frameCount, frameTime);
    evaAnimations.SetMoveRightAnimation(moveRightFile, frameCount, frameTime);
}
