#include "Penguins.h"
#include "InputManager.h"
#include "Camera.h"
#include "Game.h"
#include "Bullet.h"
#include "Timer.h"
#include "Animation.h"

#include <iostream>

#define UNUSED_VAR (void)
#define ACC 3.0
#define MAX_SPEED 3.0
#define ANG_V M_PI

Penguins::Penguins(float x, float y) : bodySp("img/penguin.png"),
	cannonSp("img/cubngun.png"), sound("audio/boom.wav")
{
	animationImg = "img/penguindeath.png";
	frameCount = 5;
	speed = Vec2(0.0, 0.0);
	hp = 20;
	linearSpeed = cannonAngle = 0.0;
	box.pos.x = x;
	box.pos.y = y;
	box.dim.x = bodySp.GetWidth();
	box.dim.y = bodySp.GetHeight();
	player = this;
	cannonAngle = 0;
}

Penguins::~Penguins(void)
{
	player = nullptr;
}

void Penguins::Update(float dt)
{
	const float cooldown = 0.25;
	static float oldTime = 0.0;
	static Timer timer = Timer();

	timer.Update(dt);
	InputManager input = InputManager::GetInstance();

	cannonAngle = atan2((input.GetMouseY()+Camera::pos.y)-box.pos.y,
			(input.GetMouseX()+Camera::pos.x)-box.pos.x);
	if (input.MousePress(LEFT_MOUSE_BUTTON) && timer.Get()-oldTime >= cooldown)
	{
		oldTime = timer.Get();
		Shoot();
	}

	if (input.IsKeyDown(D_KEY))
		rotation += ANG_V*dt;
	if (input.IsKeyDown(A_KEY))
		rotation -= ANG_V*dt;

	if (input.IsKeyDown(W_KEY))
		speed += Vec2(ACC, 0).Rotate(rotation)*dt;
	if (input.IsKeyDown(S_KEY))
		speed -= Vec2(ACC, 0).Rotate(rotation)*dt;
	
	if (speed.GetModule() > MAX_SPEED)
		speed = speed.Normalize() * MAX_SPEED;

	box.pos+=speed;
}

void Penguins::Render(void)
{
	bodySp.Render(box.pos.x - Camera::pos.x - box.dim.x/2,
			box.pos.y - Camera::pos.y - box.dim.y/2, rotation*(180/M_PI));

	cannonSp.Render(box.pos.x - Camera::pos.x - cannonSp.GetWidth()/2,
			box.pos.y - Camera::pos.y - cannonSp.GetHeight()/2,
			cannonAngle*(180/M_PI));
}

bool Penguins::IsDead(void)
{
	if (hp > 0)
		return false;

	Game::GetInstance()->GetCurrentState().AddObject(
			new Animation(box.pos, rotation, animationImg, frameCount));
	sound.Play(0);

	return true;
}

void Penguins::Shoot(void)
{
	Vec2 offset = (box.dim - Vec2(cannonSp.GetWidth(), cannonSp.GetHeight()));
	Game::GetInstance()->GetCurrentState().AddObject(new Bullet(box.pos + offset + 
				Vec2(60, 0).Rotate(cannonAngle), cannonAngle, 200, 200,
				"img/penguinbullet.png", false, 4));
}

void Penguins::NotifyCollision(GameObject &other)
{
	UNUSED_VAR other;
}

bool Penguins::Is(std::string className)
{
	return (className == "Penguins");
}

void Penguins::TakeDamage(int dmg)
{
	hp = hp - dmg;
}

