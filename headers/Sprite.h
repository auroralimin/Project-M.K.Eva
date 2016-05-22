#pragma once
#include "SDL2/SDL.h"

#include <iostream>
#include <string>
#include <memory>

class Sprite
{
	public:
		Sprite(void);
		Sprite(std::string file, int frameCount = 1, float frameTime = 1.0);
		void Open(std::string file);
		void Update(float dt);
		void SetFrame(int frame);
		void SetFrameCount(int frameCount);
		void SetFrameTime(float frameTime);
		void SetClip(int x, int y, int w, int h);
		void Render(int x = 0, int y = 0, float angle = 0.0);
		int GetWidth(void);
		int GetHeight(void);
		bool IsOpen(void);
		void SetScaleX(float x);
		void SetScaleY(float y);

	private:
		int width, height, frameCount, currentFrame;
		float frameTime, timeElapsed, scaleX, scaleY;
		std::shared_ptr<SDL_Texture> texture;
		SDL_Rect clipRect;
		SDL_Rect dstRect;
};

