#pragma once
#include <vector>
#include "TileSet.h"

/***************************************************************************//**
 * Creates a room given a tileset and a tilemap.
 ******************************************************************************/
class TileMap
{
	public:
		/**
		 * Reads a tilemap from a file and sets a tileset received by argument.
		 * @param file a string argument with the tilemap file path
		 * @param tileSet a TileSet argument with the room tile set
		 */
		TileMap(std::string file, TileSet *tileSet);

		/**
		 * Reads a tilemap from a file.
		 * @param file a string argument with the tilemap file path
		 */
		void Load(std::string file);

		/**
		 * Sets the room tileset.
		 * @param tileSet a TileSet argument with the room tile set
		 */
		void SetTileSet(TileSet *tileSet);

		/**
		 * Gives the index of a tile at a given position.
		 * @param x an int argument with the x coordinate
		 * @param y an int argument with the y coordinate
		 * @param z an int argument with the z coordinate
		 */
		int At(int x, int y, int z = 1);

		/**
		 * Renders the room considering the given camera position offset
		 * @param cameraX an int argument with the camera x coordinate
		 * @param cameraY an int argument with the camera y coordinate
		 */
		void Render(int cameraX = 0, int cameraY = 0);

		/**
		 * Renders a room given layer considering the given camera position offset
		 * @param layer an int argument with the layer value
		 * @param cameraX an int argument with the camera x coordinate
		 * @param cameraY an int argument with the camera y coordinate
		 */
		void RenderLayer(int layer, int cameraX = 0, int cameraY = 0);

		/**
		 * Gets the room width.
		 * @return Returns the room width
		 */
		int GetWidth(void);

		/**
		 * Gets the room height.
		 * @return Returns the room height
		 */
		int GetHeight(void);

		/**
		 * Gets the room depth.
		 * @return Returns the room depth
		 */
		int GetDepth(void);

	private:
		TileSet *tileSet;
		std::vector<int> tileMatrix;
		int mapWidth, mapHeight, mapDepth;
};

