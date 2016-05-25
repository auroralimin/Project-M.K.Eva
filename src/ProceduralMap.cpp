#include <ctime>
#include <iomanip>

#include "SDL2/SDL.h"
#include "Game.h"
#include "ProceduralMap.h"

int** ProceduralMap::map = nullptr;
int ProceduralMap::totalRooms = 0;
int ProceduralMap::width = 0;
int ProceduralMap::height = 0;
Sprite ProceduralMap::room1 = Sprite();
Sprite ProceduralMap::room2 = Sprite();
ProceduralMap::MapConfig ProceduralMap::config;

std::string ProceduralMap::GenerateMap(int width, int height, int totalRooms, MapConfig config)
{
	ProceduralMap::width = width;
	ProceduralMap::height = height;
	ProceduralMap::totalRooms = totalRooms;
	ProceduralMap::config = config;

	float p = (width*height)/totalRooms;
	if (p < 1)
	{
		std::cerr << "Nrooms lower than map height times map width" << std::endl;
		return nullptr;
	}

	Vec2 sparsity = Vec2((int)(p/2*config), (int)(p*config));
	if (!room1.IsOpen())
	{
		room1.Open("img/square.jpg");
		room1.SetScaleX(0.5);
		room1.SetScaleY(0.5);
	}
	if (!room2.IsOpen())
	{
		room2.Open("img/square2.jpg");
	}
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

	//PrintMap();
	//Render(true);
	for (int j = 0; j < height; ++j)
		for (int i = 0; i < width; ++i)
			if (map[i][j] == 0)
			{
				minProb = (sparsity.x-newRooms)/nPossibilities;	
				maxProb = (sparsity.y-newRooms)/nPossibilities;	
				if (CellReprodution(i, j, minProb, maxProb))
				{
					newRooms++;
				}
				nPossibilities--;
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

	Render(false);
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

	probability = maxProb;
	if (neighbors < 1 + config && (float)(rand() % 100) < probability * 100)
	{
		map[x][y] = 1;	
		return true;
	}

	map[x][y] = -1;
	return false;
}

void ProceduralMap::Render(bool renderGeneration)
{
	Sprite room;

	if (config == MapConfig::SPARSE)
		room = room1;
	if (config == MapConfig::DENSE)
		room = room2;

	int roomW = room.GetWidth(), roomH = room.GetHeight();

	for (int i = 0; i < width; ++i)
		for (int j = 0; j < height; ++j)
			if (map[i][j] == 1)
			{
					room.Render(i*roomW, j*roomH);
			}
	if (renderGeneration)
	{
		SDL_Delay(250);
		SDL_RenderPresent(Game::GetInstance()->GetRenderer());
	}
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
	map = nullptr;
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

