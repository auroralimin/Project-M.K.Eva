#pragma once
#include "SDL2/SDL.h"

#define UNUSED_VAR   (void)
#define COLOR_BLACK  {  0,   0,   0, 255}
#define COLOR_RED    {255,   0,   0, 255}
#define COLOR_WHITE  {255, 255, 255, 255}
#define COLOR_HITBOX {255,   0,   0, 100}

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
		static const bool HITBOX_MODE = false;
};

