#pragma once
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <unordered_map>
#include <memory>

class Resources
{
	public:
		static std::shared_ptr<SDL_Texture> GetImage(std::string file);
		static void ClearImages(void);
		static std::shared_ptr<Mix_Music> GetMusic(std::string file);
		static void ClearMusics(void);
		static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
		static void ClearSounds(void);
		static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
		static void ClearFonts(void);

	private:
		static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
		static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
		static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
		static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;
};

