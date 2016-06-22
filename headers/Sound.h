#pragma once
#include <string>
#include <memory>

#include "SDL2/SDL_mixer.h"

/***************************************************************************/ /**
  * This class manages a game sound effect loaded from a .wav file.
  ******************************************************************************/
class Sound
{
  public:
    /**
     * Initializes sound attributes with default values.
     */
    Sound(void);

    /**
     * Loads a sound from a given file.
     * @param file a string argument containing the sound file path
     */
    Sound(std::string file);

    /**
     * Plays a sound for a given amount of times. If this amount is -1,
     * the sound will be played in loop.
     * @param times a int argument with how many times the sound will be played.
     */
    void Play(int times);

    /**
     * Stops the sound.
     */
    void Stop(void);

    /**
     * Loads a sound from a given file.
     * @param file a string argument with the sound file path
     */
    void Open(std::string file);

    /**
     * Checks if the sound is loaded.
     * @return if the sound is open
     */
    bool IsOpen(void);

  private:
    std::shared_ptr<Mix_Chunk> chunk;
    int channel;
};

