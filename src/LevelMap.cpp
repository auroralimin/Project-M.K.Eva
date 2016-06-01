#include <iostream>

#include "LevelMap.h"
#include "TileSet.h"
#include "Camera.h"
#include "Rect.h"
#include "Collision.h"

#define TILE_SIZE 64

LevelMap::LevelMap(std::string file)
{
	Load(file);
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

	char roomsPath[200];
	fscanf(fp, "%s\n", roomsPath);

	fscanf(fp, "%d,%d,", &mapWidth, &mapHeight);
	fscanf(fp, "%f,%f,", &currentRoom.x, &currentRoom.y);

	int r;
	while(fscanf(fp, "%d,", &r) != EOF)
	{
		if (r != -1 && rooms.find(r) == rooms.end())
			rooms.emplace(r, new TileMap(roomsPath + std::to_string(r) + ".txt", tileSet));
		mapMatrix.emplace_back(r);
	}
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

bool LevelMap::IsCollidingWithWall(GameObject* obj)
{
	std::vector<Rect> wallRect = rooms[index]->GetWallRect();
	for(size_t i = 0; i < wallRect.size(); i++)
        if(Collision::IsColliding(obj->hitbox, wallRect[i], obj->rotation, 0))
			return true;

	return false;
}

