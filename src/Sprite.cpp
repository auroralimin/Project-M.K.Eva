#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(void)
{
	Sprite::texture = nullptr;
}

Sprite::Sprite(std::string file)
{
	Sprite::texture = nullptr;
	Sprite::open(file);
}

Sprite::~Sprite(void)
{
	if (Sprite::texture)
		SDL_DestroyTexture(Sprite::texture);
}

void Sprite::open(std::string file)
{
//	if (Sprite::texture)
//		SDL_DestroyTexture(texture);
	
	Sprite::texture =
		IMG_LoadTexture(Game::getInstance()->getRenderer(), file.c_str());
	if (!Sprite::texture)
	{
		std::cerr << "Failed to load texture: " << SDL_GetError() << std::endl;
		exit(EXIT_SUCCESS);
	}

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

void Sprite::render(int x, int y)
{
	dstRect.x = x;
	dstRect.y = y;
	dstRect.w = clipRect.w;
	dstRect.h = clipRect.h;
	
	SDL_RenderCopy(Game::getInstance()->getRenderer(), texture, &clipRect, &dstRect);
}

int Sprite::getWidth(void)
{
	return width;
}

int Sprite::getHeight(void)
{
	return height;
}

bool Sprite::isOpen(void)
{
	if (!Sprite::texture)
		return false;
	return true;
}

