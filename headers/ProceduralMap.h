#pragma once
#include <iostream>

#include "Sprite.h"
#include "Vec2.h"

/***************************************************************************//**
 * Static module that can procedural generates maps
 ******************************************************************************/
class ProceduralMap
{
	public:
		/**
		 * Enum with configurations of procedural generation.
		 */
		enum MapConfig
		{
			SPARSE = 1,
			DENSE = 3,
		};

		/**
		 * Procedural generate a map given some specs.
		 * @param width a int with the to be generated map max width
		 * @param heigth a int with the to be generated map max heigth
		 * @param totalRooms a int with the map total number of rooms
		 * @param config a MapConfig with the map configuration
         * @param render a bool to check if the minimap should be rendered ot not
		 */
		static std::string GenerateMap(int width, int height, int totalRooms, MapConfig config, bool Render);

	private:
		static int** map;
		static int totalRooms, width, height, nMaps;
        static bool render;
		static Vec2 firstRoom;
		static MapConfig config;
		static std::string path;

		static void SetupMap(void);
		static void Automaton(int minRoomPerGen, int nRooms, int nPossibilities);
		static bool CellReprodution(const int x, const int y, const float probability);
		static int NewPossibilities(void);
		static void Render(const bool renderGeneration, const std::string path);
		static void LabelRooms(void);
		static std::string GenerateMapFile(void);
		static void DeleteMap(void);
		static void PrintMap(void);
};

