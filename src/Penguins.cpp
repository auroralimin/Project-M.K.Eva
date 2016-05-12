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

Penguins::Penguins(float x, float y) : bodySp("img/penguin.png"), cannonSp("img/cubngun.png")
{
	animationImg = "img/penguindeath.png";
	frameCount = 5;
	speed = Vec2(0.0, 0.0);
	hp = 50;
	linearSpeed = cannonAngle = 0.0;
	box.pos.x = x;
	box.pos.y = y;
	box.dim.x = bodySp.getWidth();
	box.dim.y = bodySp.getHeight();
	player = this;
	cannonAngle = 0;
}

Penguins::~Penguins(void)
{
	player = nullptr;
}

void Penguins::update(float dt)
{
	const float cooldown = 0.25;
	static float oldTime = 0.0;
	static Timer timer = Timer();

	timer.update(dt);
	InputManager input = InputManager::getInstance();

	cannonAngle = atan2((input.getMouseY()+Camera::pos.y)-box.pos.y,
			(input.getMouseX()+Camera::pos.x)-box.pos.x);
	if (input.mousePress(LEFT_MOUSE_BUTTON) && timer.get()-oldTime >= cooldown)
	{
		oldTime = timer.get();
		shoot();
	}

	if (input.isKeyDown(D_KEY))
		rotation += ANG_V*dt;
	if (input.isKeyDown(A_KEY))
		rotation -= ANG_V*dt;

	if (input.isKeyDown(W_KEY))
		speed += Vec2(ACC, 0).rotate(rotation)*dt;
	if (input.isKeyDown(S_KEY))
		speed -= Vec2(ACC, 0).rotate(rotation)*dt;
	
	if (speed.getModule() > MAX_SPEED)
		speed = speed.normalize() * MAX_SPEED;

	box.pos+=speed;
}

void Penguins::render(void)
{
	bodySp.render(box.pos.x - Camera::pos.x - box.dim.x/2,
			box.pos.y - Camera::pos.y - box.dim.y/2, rotation*(180/M_PI));

	cannonSp.render(box.pos.x - Camera::pos.x - cannonSp.getWidth()/2,
			box.pos.y - Camera::pos.y - cannonSp.getHeight()/2,
			cannonAngle*(180/M_PI));
}

bool Penguins::isDead(void)
{
	if (hp > 0)
		return false;

	Game::getInstance()->getState().addObject(
			new Animation(box.pos, rotation, animationImg, frameCount));

	return true;
}

void Penguins::shoot(void)
{
	Vec2 offset = (box.dim - Vec2(cannonSp.getWidth(), cannonSp.getHeight()));
	Game::getInstance()->getState().addObject(new Bullet(box.pos + offset + 
				Vec2(60, 0).rotate(cannonAngle), cannonAngle, 200, 200,
				"img/penguinbullet.png", false, 4));
}

void Penguins::notifyCollision(GameObject &other)
{
	UNUSED_VAR other;
}

bool Penguins::is(std::string className)
{
	return (className == "Penguins");
}

void Penguins::takeDamage(int dmg)
{
	hp = hp - dmg;
}

