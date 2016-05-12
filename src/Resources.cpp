#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;

SDL_Texture* Resources::GetImage(std::string file)
{
	SDL_Texture *img;
	std::unordered_map<std::string, SDL_Texture*>::const_iterator element =
		imageTable.find(file);

	if (element == imageTable.end())
	{
		img = IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());
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

void Resources::ClearImages(void)
{
	for (auto element : imageTable)
		SDL_DestroyTexture(element.second);
}

