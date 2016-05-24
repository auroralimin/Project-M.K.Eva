#pragma once
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <unordered_map>
#include <memory>

/***************************************************************************//**
 * This class manages the game resources.
 * In addition, each resource will not be loaded more than once.
 ******************************************************************************/
class Resources
{
	public:
		/**
		 * Gets a image resource, given a file.
		 * @param file a string containing the image file path
		 * @return A shared pointer to the requested image resource
		 */
		static std::shared_ptr<SDL_Texture> GetImage(std::string file);

		/**
		 * Clears all images resources from game memory.
		 */
		static void ClearImages(void);

		/**
		 * Gets a music resource, given a file.
		 * @param file a string containing the music file path
		 * @return A shared pointer to the requested music resource
		 */
		static std::shared_ptr<Mix_Music> GetMusic(std::string file);

		/**
		 * Clear all musics resources from game memory.
		 */
		static void ClearMusics(void);

		/**
		 * Gets a sound resource, given a file.
		 * @param file a string containing the sound file path
		 * @return A shared pointer to the requested sound resource
		 */
		static std::shared_ptr<Mix_Chunk> GetSound(std::string file);

		/**
		 * Clears all sounds resources from game memory.
		 */
		static void ClearSounds(void);

		/**
		 * Gets a font resource, given a file.
		 * @param file a string containing the font file path
		 * @return A shared pointer to the requested font resource
		 */
		static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);

		/**
		 * Clears all fonts resources from game memory.
		 */
		static void ClearFonts(void);

	private:
		static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
		static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
		static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
		static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;
};

