#pragma once
#include "SDL2/SDL_image.h"
#include <iostream>
#include <unordered_map>
#include <memory>

class Resources
{
	public:
		static std::shared_ptr<SDL_Texture> GetImage(std::string file);
		static void ClearImages(void);

	private:
		static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
};

