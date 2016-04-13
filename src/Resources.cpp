#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;

SDL_Texture* Resources::getImage(std::string file)
{
	SDL_Texture *img;
	std::unordered_map<std::string, SDL_Texture*>::const_iterator element =
		imageTable.find(file);

	if (element == imageTable.end())
	{
		img = IMG_LoadTexture(Game::getInstance()->getRenderer(), file.c_str());
		if (!img)
		{
			std::cerr << "Failed to get image: " << SDL_GetError() << std::endl;
			exit(EXIT_SUCCESS);
		}
		imageTable.emplace(file, img);
		return img;
	}

	return element->second;
}

void Resources::clearImages(void)
{
	for (auto element : imageTable)
		SDL_DestroyTexture(element.second);
}

