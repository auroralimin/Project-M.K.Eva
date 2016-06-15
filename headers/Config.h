#pragma once
#include "SDL2/SDL.h"

#define UNUSED_VAR   (void)
#define COLOR_BLACK		{  0,   0,   0, 255}
#define COLOR_RED    	{255,   0,   0, 255}
#define COLOR_WHITE  	{255, 255, 255, 255}
#define COLOR_HITBOX	{255,   0,   0, 150}
#define COLOR_T_GREY_1 	{245, 184,  50, 125}
#define COLOR_T_GREY_2 	{  0, 100, 100, 200}
#define COLOR_T_GREY_3 	{  0, 200, 200, 230}

/***************************************************************************//**
 * The game config file.
 * Contains macros, constants and global values.
 ******************************************************************************/
class Config
{
	public:
		/*
		 * Attribute to set if the game is on debug mode.
		 */
		static const bool DEBUG = false;

		/*
		 * Attribute to set if the game is on hitbox mode.
		 */
		static const bool HITBOX_MODE = true;

		static float Rand(float fMin, float fMax) {
			float f = (float)rand() / RAND_MAX;
			return fMin + f*(fMax - fMin);
		}
};

