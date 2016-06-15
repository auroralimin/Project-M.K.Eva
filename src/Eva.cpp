#include "Eva.h"
#include "Camera.h"
#include "InputManager.h"
#include "Game.h"
#include "Config.h"
#include "Animation.h"
#include "Bullet.h"

#include <iostream>

Eva* Eva::player = nullptr;

Eva::Eva(Vec2 pos) :
    evaAnimations(5)
{
    frameCounts = new int[5]{6, 6, 6, 6, 6};
    frameTimes = new float[5]{0.08, 0.08, 0.08, 0.08, 0.08};
    SetClass(BASE);

    moveSpeed = 200;
    box.pos = pos;
    box.dim = Vec2(evaAnimations.GetSpriteWidth(),
                         evaAnimations.GetSpriteHeight());
	hitbox.dim = Vec2(box.dim.x/2, box.dim.y/4);
	hitbox.pos = Vec2(box.pos.x + 35, box.pos.y + 90);
    rotation = 0;
    hp = 100;
    player = this;
}

Eva::~Eva()
{
    player = nullptr;
}

void Eva::Render()
{
	int color[4] = COLOR_HITBOX;
	if (Config::HITBOX_MODE)
		hitbox.RenderFilledRect(color);
	evaAnimations.Render(box.pos.x - Camera::pos.x, box.pos.y - Camera::pos.y);
}

void Eva::Update(float dt)
{
	Vec2 speed = Vec2(0, 0);
	previousPos = box.pos;
	bool isMoving = false;
	InputManager &manager = InputManager::GetInstance();

    if (manager.KeyPress(Q_KEY)) {
        currentClass -= 1;
        if (currentClass < 0)
            currentClass = 2;
        SetClass((Classes)currentClass);
    } else if (manager.KeyPress(E_KEY)) {
        currentClass += 1;
        if (currentClass > 2)
            currentClass = 0;
        SetClass((Classes)currentClass);
    }

    if (manager.KeyPress(SPACEBAR)) { // temporary suicide button
        TakeDamage(8000);
    }

	if (manager.IsKeyDown(D_KEY))
	{
		isMoving = true;
		if (!(manager.IsKeyDown(S_KEY)) && !(manager.IsKeyDown(W_KEY)))
            evaAnimations.SetCurrentState(Animations::MOVING_RIGHT);
		speed.x += 1;
	}
	if (manager.IsKeyDown(A_KEY))
	{
		isMoving = true;
		if (!(manager.IsKeyDown(S_KEY)) && !(manager.IsKeyDown(W_KEY)))
            evaAnimations.SetCurrentState(Animations::MOVING_LEFT);
		speed.x -= 1;
	}
	if (manager.IsKeyDown(S_KEY))
	{
		isMoving = true;
        evaAnimations.SetCurrentState(Animations::MOVING_DOWN);
		speed.y += 1;
	}
	if (manager.IsKeyDown(W_KEY))
	{
		isMoving = true;
        evaAnimations.SetCurrentState(Animations::MOVING_UP);
		speed.y -= 1;
	}
	if (!isMoving)
        evaAnimations.SetCurrentState(Animations::IDLE);

	box.pos += speed.Normalize() * moveSpeed * dt;

	hitbox.pos = Vec2(previousPos.x + 35, box.pos.y + 90);
	if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
		box.pos.y = previousPos.y;

	hitbox.pos = Vec2(box.pos.x + 35, previousPos.y + 90);
	if(Game::GetInstance()->GetCurrentState().IsCollidingWithWall(this))
		box.pos.x = previousPos.x;

	hitbox.pos = Vec2(box.pos.x + 35, box.pos.y + 90);
	evaAnimations.Update(dt);
}

bool Eva::IsDead()
{
	return (hp <= 0);
}

void Eva::NotifyCollision(GameObject &other, bool movement)
{
	if (other.Is("Bullet")) {
		Bullet& bullet = (Bullet&) other;
		if (bullet.targetsPlayer) {
			TakeDamage(10);
		}
	} if (other.Is("Ball")) {
		TakeDamage(0);
	} else if (movement && (!other.Is("Ball"))) {
		box.pos = previousPos;
		if (other.Is("MekaBug")) {
			TakeDamage(5);
		}
	}
}

bool Eva::Is(std::string className)
{
	return (className == std::string("Eva"));
}

void Eva::TakeDamage(float dmg)
{
	hp -= dmg;
    if (IsDead()) {
        Game::GetInstance()->GetCurrentState().AddObject(
			new Animation(box.GetCenter(), 0, std::string("sprites/eva/death/EVA-") 
			+ classes[currentClass] + std::string("-DEATH.png"), 16, 0.08));
    }
}

void Eva::SetAnimationFile(int index, std::string file)
{
	files[index] = file;
    evaAnimations.SetAnimation(index, file, frameCounts[index], frameTimes[index]);
}

void Eva::SetFrameTime(int index, float time)
{
    frameTimes[index] = time;
    evaAnimations.SetAnimation(index, files[index], frameCounts[index], frameTimes[index]);
}

void Eva::SetFrameCount(int index, int count)
{
    frameCounts[index] = count;
    evaAnimations.SetAnimation(index, files[index], frameCounts[index], frameTimes[index]);
}

void Eva::SetAnimationFileSet(Classes pClass)
{
    std::string path("sprites/eva/movement/EVA-");
    std::string tFiles[5] = {path + classes[pClass] + std::string("-IDLE.png"),
                             path + classes[pClass] + std::string("-UP.png"),
                             path + classes[pClass] + std::string("-DOWN.png"),
                             path + classes[pClass] + std::string("-LEFT.png"),
                             path + classes[pClass] + std::string("-RIGHT.png")};
    files = tFiles;
    for (int i = 0; i < 5; i++) {
        evaAnimations.SetAnimation(i, files[i], frameCounts[i], frameTimes[i]);
    }
}

void Eva::SetClass(Classes c)
{
	currentClass = c;
	SetAnimationFileSet(c);
}

