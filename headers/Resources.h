#pragma once
#include "SDL2/SDL_image.h"
#include <iostream>
#include <unordered_map>

class Resources
{
	public:
		static SDL_Texture* getImage(std::string file);
		static void clearImages(void);

	private:
		static std::unordered_map<std::string, SDL_Texture*> imageTable;
};

