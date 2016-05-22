#include "Text.h"
#include "Game.h"
#include "Resources.h"

#define BLACK {0, 0, 0, 0}

Text::Text(std::string fontFile, int fontSize, TextStyle style,
		std::string text, SDL_Color color, int x, int y) :
	texture(nullptr), fontSize(fontSize), style(style), text(text), color(color)
{
	font = Resources::GetFont(fontFile, fontSize);
	SetPos(x, y, true, true);
	RemakeTexture();
}

Text::~Text(void)
{
	if (texture != nullptr)
		SDL_DestroyTexture(texture);
}

void Text::Render(int CameraX, int CameraY)
{
	clipRect.x = 0 + CameraX;
	clipRect.y = 0 + CameraY;
	SDL_RenderCopy(Game::GetInstance()->GetRenderer(), texture, &clipRect, &dstRect);
}

void Text::SetPos(int x, int y, bool centerX, bool centerY)
{
	if (centerX)
		box.pos.x -= box.dim.x/2;
	if (centerY)
		box.pos.y -= box.dim.y/2;
	dstRect.x = clipRect.x = box.pos.x = x;
	dstRect.y = clipRect.y = box.pos.y = y;
}

void Text::SetText(std::string text)
{
	this->text = text;
	RemakeTexture();
}

void Text::SetColor(SDL_Color color)
{
	this->color = color;
	RemakeTexture();
}

void Text::SetStyle(TextStyle style)
{
	this->style = style;
	RemakeTexture();
}

void Text::SetFontSize(int fontSize)
{
	this->fontSize = fontSize;
	RemakeTexture();
}

/*
 * Private Methods
 */
void Text::RemakeTexture(void)
{
	SDL_Surface *surface = nullptr;
	if (texture != nullptr)
		SDL_DestroyTexture(texture);

	switch(style)
	{
		case TextStyle::SOLID:
			surface = TTF_RenderText_Solid(font.get(), text.c_str(), color);
			break;
		case TextStyle::SHADED:
			surface = TTF_RenderText_Shaded(font.get(), text.c_str(), color, BLACK);
			break;
		case TextStyle::BLENDED:
			surface = TTF_RenderText_Blended(font.get(), text.c_str(), color);
			break;
		default:
			//do nothing
			break;
	}
	dstRect.w = clipRect.w = box.dim.x = surface->w;
	dstRect.h = clipRect.h = box.dim.y = surface->h;
	texture = SDL_CreateTextureFromSurface(Game::GetInstance()->GetRenderer(),
			surface);
	SDL_FreeSurface(surface);

}

