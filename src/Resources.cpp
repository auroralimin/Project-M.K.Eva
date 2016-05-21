#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;

std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file)
{
	SDL_Texture *img;

	if (imageTable.find(file) == imageTable.end())
	{
		img = IMG_LoadTexture(Game::GetInstance()->GetRenderer(), file.c_str());
		if (!img)
		{
			std::cerr << "Failed to get image: " << SDL_GetError() << std::endl;
			exit(EXIT_SUCCESS);
		}
		std::shared_ptr<SDL_Texture> texture(img,
				[](SDL_Texture *ptr){
					SDL_DestroyTexture(ptr);
				});
		imageTable.emplace(file, texture);
		return texture;
	}

	return imageTable.find(file)->second;
}

void Resources::ClearImages(void)
{
	for (auto element : imageTable)
	{
		if (element.second.unique())
		imageTable.erase(element.first);	
	}
}

