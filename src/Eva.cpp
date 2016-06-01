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
    rotation = 0;
    hp = 100; //temp value
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
    this->box.pos = pos;
    this->box.dim = Vec2(evaAnimations.GetSpriteWidth(),
                         evaAnimations.GetSpriteHeight());
    this->frameCount = frameCount;
    rotation = 0;
    hp = 100; //temp value
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
	{
		SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0, 200);
		SDL_SetRenderDrawBlendMode(Game::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
		SDL_Rect rect;
		rect.x = box.pos.x;
		rect.y = box.pos.y;
		rect.w = box.dim.x;
		rect.h = box.dim.y;
		SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &rect);
	}
	evaAnimations.Render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y);
}

void Eva::Update(float dt)
{
	Vec2 previousPos = box.pos;
	bool isMoving = false;
	Vec2 speed = Vec2(0, 0);
	InputManager &manager = InputManager::GetInstance();

    if (manager.KeyPress(NUM_1_KEY)) {
        if (currentClass != BASE){
            currentClass = BASE;
            SetAnimationFileSet(BASE);
        }
    }

    if (manager.KeyPress(NUM_2_KEY)) {
        if (currentClass != DECKER){
            currentClass = DECKER;
            SetAnimationFileSet(DECKER);
        }
    }

    if (manager.KeyPress(NUM_3_KEY)) {
        if (currentClass != GUNSLINGER){
            currentClass = GUNSLINGER;
            SetAnimationFileSet(GUNSLINGER);
        }
    }


	if (manager.IsKeyDown(D_KEY))
	{
		isMoving = true;
		if (!(manager.IsKeyDown(S_KEY)) && !(manager.IsKeyDown(W_KEY)))
			evaAnimations.SetCurrentState(AnimationFSM::MOVING_RIGHT);
		speed.x += dt;
	}
	if (manager.IsKeyDown(A_KEY))
	{
		isMoving = true;
		if (!(manager.IsKeyDown(S_KEY)) && !(manager.IsKeyDown(W_KEY)))
			evaAnimations.SetCurrentState(AnimationFSM::MOVING_LEFT);
		speed.x -= dt;
	}
	if (manager.IsKeyDown(S_KEY))
	{
		isMoving = true;
		evaAnimations.SetCurrentState(AnimationFSM::MOVING_DOWN);
		speed.y += dt;
	}
	if (manager.IsKeyDown(W_KEY))
	{
		isMoving = true;
		evaAnimations.SetCurrentState(AnimationFSM::MOVING_UP);
		speed.y -= dt;
	}

	if (!isMoving)
		evaAnimations.SetCurrentState(AnimationFSM::IDLE);

	box.pos += speed.Normalize() * moveSpeed;
	evaAnimations.Update(dt);

	if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
		box.pos = previousPos;
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
    std::string adress("sprites/eva/movement/EVA-");
    std::string set;
    switch (pClass) {
    case BASE:
        set = std::string("BASE");
        break;
    case DECKER:
        set = std::string("DECKER");
        break;
    case GUNSLINGER:
        set = std::string("GUN");
        break;
    default:
        set = std::string("BASE");
        break;
    }
    std::string tfiles[5] = {adress + set + std::string("-PARADA.png"),
                             adress + set + std::string("-UP.png"),
                             adress + set + std::string("-DOWN.png"),
                             adress + set + std::string("-LEFT.png"),
                             adress + set + std::string("-RIGHT.png")};
    files = tfiles;
    for (int i = 0; i < 5; i++) {
        evaAnimations.SetAnimation(i, files[i], frameCount, frameTime);
    }
}
