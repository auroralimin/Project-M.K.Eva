#include "Eva.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"
#include "Config.h"

#include <iostream>

Eva* Eva::player = nullptr;

Eva::Eva(): evaAnimations()
{
    box.pos = Vec2();
    box.dim = Vec2();
    hitbox.pos = Vec2();
    hitbox.dim = Vec2();
    rotation = 0;
    hp = 100;
    frameCount = 1;
    frameTime = 1.0f;
    moveSpeed = 150;
    currentClass = BASE;
}

Eva::Eva(Vec2 pos, std::string *files, int frameCount, float frameTime, int moveSpeed) :
	files(files), frameTime(frameTime), moveSpeed(moveSpeed),
	evaAnimations(files, frameCount, frameTime)
{
	this->files = files;
    this->frameCount = frameCount;
    box.pos = pos;
    box.dim = Vec2(evaAnimations.GetSpriteWidth(),
                         evaAnimations.GetSpriteHeight());
	hitbox.dim = Vec2(box.dim.x/2, box.dim.y/4);
	hitbox.pos = Vec2(box.pos.x + 20, box.pos.y + 60);
    rotation = 0;
    hp = 100;
    player = this;
    currentClass = BASE;
}

Eva::~Eva()
{
    player = nullptr;
}

void Eva::Render()
{
	if (Config::HITBOX_MODE)
		hitbox.RenderFilledRect();
	evaAnimations.Render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y);
}

void Eva::Update(float dt)
{
	Vec2 previousPos = box.pos;
	bool isMoving = false;
	Vec2 speed = Vec2(0, 0);
	InputManager &manager = InputManager::GetInstance();

    if (manager.KeyPress(NUM_1_KEY) && currentClass != BASE)
		SetClass(BASE);
	else if (manager.KeyPress(NUM_2_KEY) && currentClass != DECKER)
		SetClass(DECKER);
	else if (manager.KeyPress(NUM_3_KEY) && currentClass != GUNSLINGER)
		SetClass(GUNSLINGER);

	if (manager.IsKeyDown(D_KEY))
	{
		isMoving = true;
		if (!(manager.IsKeyDown(S_KEY)) && !(manager.IsKeyDown(W_KEY)))
			evaAnimations.SetCurrentState(AnimationFSM::MOVING_RIGHT);
		speed.x += 1;
	}
	if (manager.IsKeyDown(A_KEY))
	{
		isMoving = true;
		if (!(manager.IsKeyDown(S_KEY)) && !(manager.IsKeyDown(W_KEY)))
			evaAnimations.SetCurrentState(AnimationFSM::MOVING_LEFT);
		speed.x -= 1;
	}
	if (manager.IsKeyDown(S_KEY))
	{
		isMoving = true;
		evaAnimations.SetCurrentState(AnimationFSM::MOVING_DOWN);
		speed.y += 1;
	}
	if (manager.IsKeyDown(W_KEY))
	{
		isMoving = true;
		evaAnimations.SetCurrentState(AnimationFSM::MOVING_UP);
		speed.y -= 1;
	}

	if (!isMoving)
		evaAnimations.SetCurrentState(AnimationFSM::IDLE);

	box.pos += speed.Normalize() * moveSpeed * dt;
	hitbox.pos = Vec2(box.pos.x + 20, box.pos.y + 60);

	if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
	{
		box.pos = previousPos;
		hitbox.pos = Vec2(box.pos.x + 20, box.pos.y + 60);
	}

	evaAnimations.Update(dt);
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

void Eva::SetAnimationFileSet(Classes pClass)
{
    std::string path("sprites/eva/movement/EVA-");
    std::string tFiles[5] = {path + classes[pClass] + std::string("-PARADA.png"),
                             path + classes[pClass] + std::string("-UP.png"),
                             path + classes[pClass] + std::string("-DOWN.png"),
                             path + classes[pClass] + std::string("-LEFT.png"),
                             path + classes[pClass] + std::string("-RIGHT.png")};
    for (int i = 0; i < 5; i++)
        evaAnimations.SetAnimation(i, tFiles[i], frameCount, frameTime);
}

void Eva::SetClass(Classes c)
{
	currentClass = c;
	SetAnimationFileSet(c);
}

