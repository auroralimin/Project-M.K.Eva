#pragma once
#include <string>
#include <memory>

#include "SDL2/SDL_mixer.h"

/***************************************************************************//**
 * This class manages a game music loaded from a file (preferably a .ogg).
 ******************************************************************************/
class Music
{
	public:
		/**
		 * Initializes music with a null pointer.
		 */
		Music(void);

		/**
		 * Loads the music from a given file.
		 * @param file a string argument with the music file path
		 */
		Music(std::string file);

		/**
		 * Play a music for a given amount of times. If this amount is -1,
		 * the music will be played in loop.
		 * @param times a int argument with how many times the music will be played.
		 */
		void Play(int times);

		/**
		 * Stops the music.
		 */
		void Stop(void);

		/**
		 * Load a music from a given file.
		 * @param file a string argument with the music file path
		 */
		void Open(std::string file);

		/**
		 * Checks if the music is loaded.
		 * @return if the music is open
		 */
		bool IsOpen(void);

	private:
		std::shared_ptr<Mix_Music> music;
};

