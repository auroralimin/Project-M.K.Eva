#pragma once
#include <string>
#include <memory>

#include "SDL2/SDL_mixer.h"

class Music
{
	public:
		Music(void);
		Music(std::string file);
		void Play(int times);
		void Stop(void);
		void Open(std::string file);
		bool IsOpen(void);

	private:
		std::shared_ptr<Mix_Music> music;
};

