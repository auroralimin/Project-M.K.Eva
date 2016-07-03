#pragma once
#include "SDL2/SDL.h"

#ifdef WINDOWS
#define M_PI 3.14159265359
#endif

#define SCREEN_PADDING 40
#define SCREEN_W 1280
#define SCREEN_H 704

#define TILE_SIZE 64
#define PROCEDURAL_GENERATED_SET 1
#define UNUSED_VAR (void)
#define COLOR_BLACK                                                            \
    {                                                                          \
        0, 0, 0, 255                                                           \
    }
#define COLOR_RED                                                              \
    {                                                                          \
        255, 0, 0, 255                                                         \
    }
#define COLOR_WHITE                                                            \
    {                                                                          \
        255, 255, 255, 255                                                     \
    }
#define COLOR_HITBOX                                                           \
    {                                                                          \
        255, 0, 0, 150                                                         \
    }
#define COLOR_ATTACK_HITBOX                                                    \
    {                                                                          \
        0, 255, 0, 150                                                         \
    }
#define COLOR_T_GREY_1                                                         \
    {                                                                          \
        245, 184, 50, 125                                                      \
    }
#define COLOR_T_GREY_2                                                         \
    {                                                                          \
        0, 100, 100, 200                                                       \
    }
#define COLOR_T_GREY_3                                                         \
    {                                                                          \
        0, 200, 200, 230                                                       \
    }
#define COLOR_T_GREY_4                                                         \
    {                                                                          \
      200, 200, 200, 100                                                       \
    }

/***************************************************************************/ /**
  * The game config file.
  * Contains macros, constants and global values.
  ******************************************************************************/
class Config
{
  public:
    enum directions { UP, LEFT, DOWN, RIGHT };

    /*
     * Attribute to set if the game is on debug mode.
     */
    static const bool DEBUG = true;

    /*
     * Attribute to set if the game is on hitbox mode.
     */
    static const bool HITBOX_MODE = false;

    static const bool ATTACK_HITBOX_MODE = false;

    static int Rand(int fMin, int fMax)
    {
        return fMin + (rand() % (fMax - fMin + 1));
    }
};

