#pragma once
#include "SDL2/SDL.h"

#include <iostream>
#include <string>

class Sprite
{
	public:
		Sprite(void);
		Sprite(std::string file);
		void open(std::string file);
		void setClip(int x, int y, int w, int h);
		void render(int x, int y, float angle = 0.0);
		int getWidth(void);
		int getHeight(void);
		bool isOpen(void);
		void setScaleX(float x);
		void setScaleY(float y);

	private:
		int width, height;
		float scaleX, scaleY;
		SDL_Texture *texture;
		SDL_Rect clipRect;
		SDL_Rect dstRect;
};

