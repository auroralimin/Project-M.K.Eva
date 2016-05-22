#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;

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

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file)
{
	Mix_Music *music;

	if (musicTable.find(file) == musicTable.end())
	{
		music = Mix_LoadMUS(file.c_str());
		if (!music)
		{
			std::cerr << "Failed to get music: " << SDL_GetError() << std::endl;
			exit(EXIT_SUCCESS);
		}
		std::shared_ptr<Mix_Music> mixMusic(music,
				[](Mix_Music *ptr){
					Mix_FreeMusic(ptr);
				});
		musicTable.emplace(file, mixMusic);
		return mixMusic;
	}

	return musicTable.find(file)->second;
}

void Resources::ClearMusics(void)
{
	for (auto element : musicTable)
	{
		if (element.second.unique())
		musicTable.erase(element.first);	
	}
}

