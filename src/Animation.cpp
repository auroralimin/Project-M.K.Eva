#include "Animation.h"
#include "Camera.h"
#include "Config.h"


Animation::Animation(Vec2 pos, float rotation, std::string sprite,
		int frameCount, float frameTime, bool ends) : 
		sp(sprite, frameCount, frameTime), endTimer(), oneTimeOnly(ends)
{
	animationImg = "";
	box.pos = pos;
	this->rotation = rotation;
	box.dim.x = sp.GetWidth();
	box.dim.y = sp.GetHeight();
	timeLimit = frameCount*frameTime;
}

void Animation::Update(float dt)
{
	sp.Update(dt);
	endTimer.Update(dt);
}

void Animation::Render(void)
{
	sp.Render(box.pos.x - Camera::pos.x - box.dim.x/2,
			box.pos.y - Camera::pos.y - box.dim.y/2, rotation);
}

bool Animation::IsDead(void)
{
	return (oneTimeOnly && endTimer.Get() >= timeLimit);
}

void Animation::NotifyCollision(GameObject &other, bool movement)
{
	UNUSED_VAR other;
	UNUSED_VAR movement;
	//D0 NOTHING
}

bool Animation::Is(std::string className)
{
	return (className == "Animation");
}

void Animation::TakeDamage(float dmg)
{
	UNUSED_VAR dmg;
	//D0 NOTHING
}
