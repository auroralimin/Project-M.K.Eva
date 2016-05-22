#pragma once
#include <string>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "SDL2/SDL_image.h"
#include "Rect.h"

class Text
{
	public:
		enum TextStyle
		{
			SOLID,
			SHADED,
			BLENDED
		};
		Text(void);
		Text(std::string fontFile, int fontSize, TextStyle style,
				std::string text, SDL_Color color, int x = 0, int y = 0);
		~Text(void);
		void Render(int CameraX = 0, int CameraY = 0);
		void SetPos(int x, int y, bool centerX = false, bool centerY = false);
		void SetText(std::string text);
		void SetColor(SDL_Color color);
		void SetStyle(TextStyle style);
		void SetFontSize(int fontSize);

	private:
		SDL_Texture *texture;
		int fontSize;
		TextStyle style;
		std::string text;
		SDL_Color color;
		std::shared_ptr<TTF_Font> font;
		Rect box;
		SDL_Rect clipRect, dstRect;

		void RemakeTexture(void);
};

