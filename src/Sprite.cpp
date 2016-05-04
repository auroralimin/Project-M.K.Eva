#include "Sprite.h"
#include "Game.h"
#include "Resources.h"

Sprite::Sprite(void) : texture(nullptr) {}

Sprite::Sprite(std::string file) 
{
	scaleX = scaleY = 1.0;
	texture = nullptr;
	open(file);
}

void Sprite::open(std::string file)
{
	texture = Resources::getImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	setClip(0, 0, width, height);
}


void Sprite::setClip(int x, int y, int w, int h)
{
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::render(int x, int y, float angle)
{
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w*scaleX;
	dstRect.h = clipRect.h*scaleY;

	SDL_RenderCopyEx(Game::getInstance()->getRenderer(), texture, &clipRect, &dstRect, angle, NULL, SDL_FLIP_NONE);
}

int Sprite::getWidth(void)
{
	return width*scaleX;
}

int Sprite::getHeight(void)
{
	return height*scaleY;
}

bool Sprite::isOpen(void)
{
	if (!Sprite::texture)
		return false;
	return true;
}

void Sprite::setScaleX(float x)
{
	scaleX = x;
}

void Sprite::setScaleY(float y)
{
	scaleY = y;
}

