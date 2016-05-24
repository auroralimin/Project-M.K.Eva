#include <ctime>
#include <iomanip>

#include "SDL2/SDL.h"
#include "ProceduralMap.h"

#define UNUSED_VAR (void)

int** ProceduralMap::map = nullptr;
int ProceduralMap::totalRooms = 0;
int ProceduralMap::width = 0;
int ProceduralMap::height = 0;
Sprite ProceduralMap::room = Sprite();

std::string ProceduralMap::GenerateMap(int width, int height, int totalRooms, MapConfig config)
{
	UNUSED_VAR config;
	//TODO implement sparsity with different map configs

	float p = (width*height)/totalRooms;
	if (p < 1)
	{
		std::cerr << "Nrooms lower than map height times map width" << std::endl;
		return nullptr;
	}

	Vec2 sparsity = Vec2((int)(p/2), (int)p);
	ProceduralMap::totalRooms = totalRooms;
	if (!room.IsOpen())
		room.Open("img/square.JPG");

	ProceduralMap::width = width;
	ProceduralMap::height = height;
	SetupMap();

	Automaton(sparsity, 1, 4);
	DeleteMap();

	//TODO save generated map on a file
	return "";
}

void ProceduralMap::SetupMap(void)
{
	map = new int*[width];
	for (int i = 0; i < width; ++i)
	{
		map[i] = new int[height];
		std::fill_n(map[i], height, -1); 
	}

	int x = 1 + std::rand() % (width-2);
	int y = 1 + std::rand() % (height-2);
	map[x][y] = 1;
	map[x-1][y] = map[x+1][y] = map[x][y-1] = map[x][y+1] = 0;
}

void ProceduralMap::Automaton(Vec2 sparsity, int nRooms, int nPossibilities)
{
	int newRooms = 0;
	float minProb, maxProb;
	
	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			if (map[i][j] == 0)
			{
				minProb = (sparsity.x-newRooms)/nPossibilities;	
				maxProb = (sparsity.y-newRooms)/nPossibilities;	
				if (CellReprodution(i, j, minProb, maxProb))
				{
					nPossibilities--;
					newRooms++;
					Render();
				}
			}

	nPossibilities += NewPossibilities();
	nRooms += newRooms;
	if (totalRooms - nRooms < sparsity.y)
	{
		sparsity.x = 1;
		sparsity.y = totalRooms-nRooms;
	}
	if (totalRooms != nRooms)
		Automaton(sparsity, nRooms, nPossibilities);

	return;
}

bool ProceduralMap::CellReprodution(const int x, const int y, const float minProb, const float maxProb)
{
	int neighbors = 0;
	float probability = 0.0;

	if ((x < 0) || ((x > 0) && (map[x-1][y] == 1)))
		neighbors++;
	if ((x >= width) || ((x < width - 1) && (map[x+1][y] == 1)))
		neighbors++;
	if ((y < 0) || ((y > 0) && (map[x][y-1] == 1)))
		neighbors++;
	if ((y >= height) || ((y < height - 1) && (map[x][y+1] == 1)))
		neighbors++;

	probability = (minProb + (1/neighbors)*(maxProb-minProb))*100;
	if (neighbors < 3 && (float)(rand() % 100) < probability)
	{
		map[x][y] = 1;	
		return true;
	}

	return false;
}

void ProceduralMap::Render(void)
{
	int roomW = room.GetWidth(), roomH = room.GetHeight();

	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			if (map[i][j] == 1)
				room.Render(i*roomW, j*roomH);
}

int ProceduralMap::NewPossibilities(void)
{
	int n = 0;

	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			if ((map[i][j] == -1) &&
					((i > 0 && map[i-1][j] == 1) ||
					 (i < width - 1 && map[i+1][j] == 1) ||
					 (j > 0 && map[i][j-1] == 1) ||
					 (j < height - 1 && map[i][j+1] == 1)))
			{
				n++;
				map[i][j] = 0;
			}

	return n;
}

void ProceduralMap::DeleteMap(void)
{
	for (int i = 0; i < width; ++i)
		delete map[i];

	delete map;
}

void ProceduralMap::PrintMap(void)
{
	for (int i = 0; i < width; ++i)
	{
		for (int j = 0; j < height; ++j)
			std::cout << std::setw(3) << map[i][j] << ",";
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

