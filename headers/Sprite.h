#pragma once
#include "SDL2/SDL.h"

#include <iostream>
#include <string>

class Sprite
{
	public:
		Sprite(void);
		Sprite(std::string file, int frameCount = 1, float frameTime = 1.0);
		void open(std::string file);
		void update(float dt);
		void setFrame(int frame);
		void setFrameCount(int frameCount);
		void setFrameTime(float frameTime);
		void setClip(int x, int y, int w, int h);
		void render(int x, int y, float angle = 0.0);
		int getWidth(void);
		int getHeight(void);
		bool isOpen(void);
		void setScaleX(float x);
		void setScaleY(float y);

	private:
		int width, height, frameCount, currentFrame;
		float frameTime, timeElapsed, scaleX, scaleY;
		SDL_Texture *texture;
		SDL_Rect clipRect;
		SDL_Rect dstRect;
};

