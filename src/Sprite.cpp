#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite(void) : texture(nullptr) {}

Sprite::Sprite(std::string file, int frameCount, float frameTime)
{
	this->frameCount = frameCount;
	currentFrame = 0;
	this->frameTime = frameTime;
	timeElapsed = 0.0;
	scaleX = scaleY = 1.0;
	texture = nullptr;
	Open(file);
}

void Sprite::Open(std::string file)
{
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width/frameCount, height);
	width = width/frameCount;
}

void Sprite::Update(float dt)
{
	timeElapsed+=dt;
	if (timeElapsed >= frameTime)
	{
		SetFrame(++currentFrame >= frameCount ? 0 : currentFrame);
		timeElapsed = 0.0;
	}
}

void Sprite::SetFrame(int frame)
{
	currentFrame = frame;
	SetClip(frame*width, 0.0, width, height);
}

void Sprite::SetFrameCount(int frameCount)
{
	this->frameCount = frameCount;
}

void Sprite::SetFrameTime(float frameTime)
{
	this->frameTime = frameTime;
}

void Sprite::SetClip(int x, int y, int w, int h)
{
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y, float angle)
{
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w*scaleX;
	dstRect.h = clipRect.h*scaleY;

	SDL_RenderCopyEx(Game::GetInstance()->GetRenderer(), texture, &clipRect, &dstRect, angle, NULL, SDL_FLIP_NONE);
}

int Sprite::GetWidth(void)
{
	return width*scaleX;
}

int Sprite::GetHeight(void)
{
	return height*scaleY;
}

bool Sprite::IsOpen(void)
{
	if (!Sprite::texture)
		return false;
	return true;
}

void Sprite::SetScaleX(float x)
{
	scaleX = x;
}

void Sprite::SetScaleY(float y)
{
	scaleY = y;
}

