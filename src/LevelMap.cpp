#include <iostream>

#include "LevelMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "Rect.h"
#include "Collision.h"

#define TILE_SIZE 32

LevelMap::LevelMap(std::string file)
{
	Load(file);
}

LevelMap::~LevelMap(void)
{
	for (auto room : rooms)
		delete room;
}

void LevelMap::Load(std::string file)
{
	FILE *fp = fopen(file.c_str(), "r");

	if (!fp)
	{
		std::cerr << "Failed to open file: " <<  file << std::endl;
		exit(EXIT_SUCCESS);	
	}

	char tileSetFile[100];
	fscanf(fp, "%s\n\n", tileSetFile);
	TileSet *tileSet = new TileSet(TILE_SIZE, TILE_SIZE, std::string(tileSetFile));

	int nRooms;
	char roomFile[100];
	fscanf(fp, "%d\n\n", &nRooms);
	for (int i = 0; i < nRooms; ++i)
	{
		fscanf(fp, "%s\n", roomFile);
		rooms.emplace_back(new TileMap(std::string(roomFile), tileSet));
	}

	int room;
	fscanf(fp, "%d,%d,", &mapWidth, &mapHeight);
	fscanf(fp, "%f,%f,", &currentRoom.x, &currentRoom.y);
	while(fscanf(fp, "%d,", &room) != EOF)
		mapMatrix.emplace_back(room);
	index = mapMatrix[currentRoom.x + (mapWidth*currentRoom.y)];

	fclose(fp);
}

void LevelMap::Render(void)
{
	rooms[index]->Render(Camera::pos.x, Camera::pos.y);
}

void LevelMap::SetCurrentRoom(Vec2 room)
{
	if (!IsOutOfLimits(room))
	{
		currentRoom = room;
		index = mapMatrix[currentRoom.x + (mapWidth*currentRoom.y)];
	}
	else
		std::cout << "Reached map out of limits" << std::endl;
}

bool LevelMap::IsOutOfLimits(Vec2 room)
{
	if (room.x < 0 || room.y < 0)
		return true;

	int newIndex = mapMatrix[room.x + (mapWidth*room.y)];
	return ((room.x >= mapWidth) || (room.y >= mapHeight) || newIndex == -1); 
}

void LevelMap::RoomUp(void)
{
	Vec2 v = Vec2(currentRoom.x, currentRoom.y - 1); 
	SetCurrentRoom(v);
}

void LevelMap::RoomDown(void)
{
	Vec2 v = Vec2(currentRoom.x, currentRoom.y + 1); 
	SetCurrentRoom(v);
}

void LevelMap::RoomLeft(void)
{
	Vec2 v = Vec2(currentRoom.x - 1, currentRoom.y); 
	SetCurrentRoom(v);
}

void LevelMap::RoomRight(void)
{
	Vec2 v = Vec2(currentRoom.x + 1, currentRoom.y); 
	SetCurrentRoom(v);
}

Vec2 LevelMap::GetCurrentRoom(void)
{
	return currentRoom;
}

int LevelMap::GetWidth(void)
{
	return mapWidth;
}

int LevelMap::GetHeight(void)
{
	return mapHeight;
}

bool LevelMap::IsCollidingWithWall(GameObject* o)
{
	std::vector<Rect> wallRect = rooms[index]->GetWallRect();
	for(size_t i = 0; i < wallRect.size(); i++)
		if(Collision::IsColliding(o->box, wallRect[i], o->rotation, 0))
			return true;

	return false;
}
