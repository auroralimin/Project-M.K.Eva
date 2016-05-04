#include <iostream>
#include "Minion.h"
#include "Camera.h"
#include "Game.h"

#define D_RADIUS 100
#define SPEED M_PI/7

Minion::Minion(GameObject *minionCenter, float arcOffSet) :
	center(minionCenter),
	sp("img/minion.png"),
	arc(arcOffSet)
{
	box.dim.x = sp.getWidth();
	box.dim.y = sp.getHeight();
	update(0.0);
	float scale = 1.0 + (rand() % 5)/10.0;
	sp.setScaleX(scale);
	sp.setScaleY(scale);
}

void Minion::update(float dt)
{
	arc += dt*SPEED;
	rotation = arc*(180/M_PI);
	box.pos.x = D_RADIUS*cos(arc) + center->box.pos.x;
	box.pos.y = D_RADIUS*sin(arc) + center->box.pos.y;
}

void Minion::render(void)
{
	sp.render(box.pos.x - Camera::pos.x - box.dim.x/2,
			box.pos.y - Camera::pos.y - box.dim.y/2, rotation);
}

bool Minion::isDead(void)
{
	return false;
}

void Minion::shoot(Vec2 pos)
{
	float angle = atan2(pos.y - box.pos.y, pos.x - box.pos.x);
	Game::getInstance()->getState().addObject(new Bullet(box.pos,
				angle, 200, 200, "img/minionbullet2.png"));
}

