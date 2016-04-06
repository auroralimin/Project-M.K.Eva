#include <iostream>
#include "Face.h"

#define UNUSED_VAR (void)

Face::Face(int x, int y, float angle)
{
	sp = new Sprite("img/penguinface.png");
	box.w = sp->getWidth();
	box.h = sp->getHeight();
	box.x = x - (int)(box.w/2);
	box.y = y - (int)(box.h/2);
	hitPoints = 1;
	this->angle = angle;
}

Face::~Face(void)
{
	delete sp;
}

void Face::damage(int damage)
{
	hitPoints -= damage;
}

void Face::update(float dt)
{
	//TODO implementar temporizacao
	UNUSED_VAR dt;
}

void Face::render(void)
{
	sp->render(box.x, box.y, angle);
}

bool Face::isDead(void)
{
	if (hitPoints > 0)
		return false;
	return true;
}

