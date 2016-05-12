#include "Animation.h"
#include "Camera.h"

#define UNUSED_VAR (void)

Animation::Animation(Vec2 pos, float rotation, std::string sprite,
		int frameCount, float frameTime, bool ends) : 
		sp(sprite, frameCount, frameTime), endTimer(), oneTimeOnly(ends)
{
	animationImg = "";
	box.pos = pos;
	this->rotation = rotation;
	box.dim.x = sp.getWidth();
	box.dim.y = sp.getHeight();
	timeLimit = frameCount*frameTime;
}

void Animation::update(float dt)
{
	sp.update(dt);
	endTimer.update(dt);
}

void Animation::render(void)
{
	sp.render(box.pos.x - Camera::pos.x - box.dim.x/2,
			box.pos.y - Camera::pos.y - box.dim.y/2, rotation);
}

bool Animation::isDead(void)
{
	return (oneTimeOnly && endTimer.get() >= timeLimit);
}

void Animation::notifyCollision(GameObject &other)
{
	UNUSED_VAR other;
	//D0 NOTHING
}

bool Animation::is(std::string className)
{
	return (className == "Animation");
}

void Animation::takeDamage(int dmg)
{
	UNUSED_VAR dmg;
	//D0 NOTHING
}
