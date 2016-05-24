#pragma once
#include "Sprite.h"

/***************************************************************************//**
 * Manages a set of tiles loaded from a file.
 ******************************************************************************/
class TileSet
{
	public:
		/**
		 * Reads a tileset from a file considering the tile dimentions.
		 * @param tileWidth an int argument with the tile width
		 * @param tileHeight an int argument with the tile height
		 * @param file a string argument with the tileset file path
		 */
		TileSet(int tileWidth, int tileHeight, std::string file);

		/**
		 * Renders a tile by its given index in a given position.
		 * @param index an int argument with the tile index
		 * @param x an int argument with the x coordinate
		 * @param y an int argument with the y coordinate
		 */
		void Render(int index, float x, float y);

		/**
		 * Gets the tile width.
		 * @return Returns the tile width
		 */
		int GetTileWidth(void);

		/**
		 * Gets the tile height.
		 * @return Returns the tile height
		 */
		int GetTileHeight(void);

	private:
		Sprite tileSet;
		int tileWidth, tileHeight;
		int rows, cols;
};

