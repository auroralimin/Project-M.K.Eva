#pragma once
#include <iostream>

#include "Sprite.h"
#include "Vec2.h"

class ProceduralMap
{
	public:
		enum MapConfig
		{
			SPARSE,
			DENSE,
			RANDOM
		};
		
		static std::string GenerateMap(int width, int height, int totalRooms, MapConfig config);
	
	private:
		static int** map;
		static int totalRooms, width, height;
		static Sprite room;

		static void SetupMap(void);
		static void Automaton(Vec2 sparsity, int nRooms, int nPossibilities);
		static bool CellReprodution(const int x, const int y, const float minProb, const float maxProb);
		static int NewPossibilities(void);
		static void Render(void);
		static void DeleteMap(void);
		static void PrintMap(void);
};

