#pragma once
#include <vector>
#include <memory>

#include "TileMap.h"
#include "Vec2.h"
#include "GameObject.h"

class LevelMap
{
	public:
		LevelMap(std::string file);
		~LevelMap(void);
		void Load(std::string file);
		void Render(void);
		void SetCurrentRoom(Vec2 room);
		bool IsOutOfLimits(Vec2 room);
		void RoomUp(void);
		void RoomDown(void);
		void RoomLeft(void);
		void RoomRight(void);
		Vec2 GetCurrentRoom(void);
		int GetWidth(void);
		int GetHeight(void);
		bool IsCollidingWithWall(GameObject* o);

	private:
		int mapWidth, mapHeight, index;
		Vec2 currentRoom;
		std::vector<TileMap*> rooms;
		std::vector<int> mapMatrix;
};

