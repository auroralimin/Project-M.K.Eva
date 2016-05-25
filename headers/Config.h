#pragma once
#include "SDL2/SDL.h"

#define UNUSED_VAR   (void)
#define COLOR_BLACK  {  0,   0,   0, 255}
#define COLOR_RED    {255,   0,   0, 255}
#define COLOR_WHITE  {255, 255, 255, 255}
#define COLOR_HITBOX {255,   0,   0, 100}

class Config
{
	public:
		static const bool DEBUG = false;
		static const bool HITBOX_MODE = false;

		struct Color {
		};

		static const Color c;
};

