#include "Rect.h"
#include "Game.h"

#include <iostream>
#include <cmath>

Rect::Rect(void)
{
	pos.x = pos.y = dim.x = dim.y = 0.0;
}

Rect::Rect(Vec2 pos, Vec2 dim) : pos(pos), dim(dim) {}

void Rect::SumWithVec2(Vec2 v)
{
	pos += v;
}

bool Rect::IsInside(Vec2 area)
{
	if ((pos.x <= area.x) && (pos.x > area.x - dim.x) &&
		(pos.y <= area.y) && (pos.y > area.y - dim.y))
		return true;
	return false;
}

Vec2 Rect::GetCenter(void)
{
	return pos + dim/2;
}

void Rect::RenderFilledRect(int color[4])
{
	SDL_Rect rect;

	rect.x = pos.x;
	rect.y = pos.y;
	rect.w = dim.x;
	rect.h = dim.y;

	SDL_Renderer *renderer = Game::GetInstance()->GetRenderer();
	SDL_SetRenderDrawColor(renderer, color[0], color[1], color[2], color[3]);
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderFillRect(renderer, &rect);
}

