#pragma once
#include "SDL2/SDL.h"

#include <iostream>
#include <string>

class Sprite
{
	public:
		Sprite(void);
		Sprite(std::string file);
		~Sprite(void);
		void open(std::string file);
		void setClip(int x, int y, int w, int h);
		void render(int x, int y);
		int getWidth(void);
		int getHeight(void);
		bool isOpen(void);
	private:
		SDL_Texture *texture;
		int width;
		int height;
		SDL_Rect clipRect;
		SDL_Rect dstRect;
};

