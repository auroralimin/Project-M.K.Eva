#include "Eva.h"
#include "Camera.h"
#include "InputManager.h"

#define UNUSED_VAR (void)

Eva::Eva(): evaAnimations()
{
    box.pos = Vec2();
    box.dim = Vec2();
    rotation = 0;
    hp = 100; //temp value
    frameCount = 1;
    frameTime = 1.0f;
    moveSpeed = 150;
}

Eva::Eva(Vec2 pos, std::string *files, int frameCount, float frameTime, int moveSpeed) :
	files(files), frameTime(frameTime), moveSpeed(moveSpeed),
	evaAnimations(files, frameCount, frameTime)
{
	this->files = files;
    this->box.pos = pos;
    this->box.dim = Vec2(evaAnimations.GetSpriteWidth()/frameCount,
                         evaAnimations.GetSpriteHeight());
    rotation = 0;
    hp = 100; //temp value
}

void Eva::Render()
{
    evaAnimations.Render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y);
}

void Eva::Update(float dt)
{
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
}

bool Eva::IsDead()
{
    return (hp <= 0);
}

void Eva::NotifyCollision(GameObject &other)
{
	UNUSED_VAR other;
    //TODO
}

bool Eva::Is(std::string className)
{
    return (className == std::string("Eva"));
}

void Eva::TakeDamage(int dmg)
{
    hp -= dmg;
}

void Eva::SetAnimationFile(int index, std::string file)
{
    files[index] = file;
    evaAnimations.SetAnimation(index, file, frameCount, frameTime);
}

void Eva::SetFrameTime(float time)
{
    frameTime = time;
	for (int i = 0; i < 5; ++i)
 	   evaAnimations.SetAnimation(i, files[i], frameCount, frameTime);
}

void Eva::SetFrameCount(int count)
{
    frameCount = count;
	for (int i = 0; i < 5; ++i)
 	   evaAnimations.SetAnimation(i, files[i], frameCount, frameTime);
}
