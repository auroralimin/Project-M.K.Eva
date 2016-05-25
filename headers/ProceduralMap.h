#pragma once
#include <iostream>

#include "Sprite.h"
#include "Vec2.h"

class ProceduralMap
{
	public:
		enum MapConfig
		{
			SPARSE = 1,
			DENSE = 3,
		};

		static std::string GenerateMap(int width, int height, int totalRooms, MapConfig config);

	private:
		static int** map;
		static int totalRooms, width, height;
		static Sprite room1, room2;
		static MapConfig config;

		static void SetupMap(void);
		static void Automaton(int minRoomPerGen, int nRooms, int nPossibilities);
		static bool CellReprodution(const int x, const int y, const float probability);
		static int NewPossibilities(void);
		static void Render(bool renderGeneration);
		static void DeleteMap(void);
		static void PrintMap(void);
};

