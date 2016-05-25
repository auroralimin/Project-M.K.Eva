#include "TileMap.h"
#include "Game.h"
#include "Vec2.h"
#include <SDL2/SDL.h>

#define UNUSED_VAR (void)
#define HITBOX_MODE true

TileMap::TileMap(std::string file, TileSet *tileSet) : tileSet(tileSet)
{
	Load(file);
}

void TileMap::Load(std::string file)
{
	int tile;
	FILE *fp = fopen(file.c_str(), "r");

	if (!fp)
	{
		std::cerr << "Failed to open file: " <<  file << std::endl;
		exit(EXIT_SUCCESS);	
	}

	fscanf(fp, "%d,%d,%d,", &mapWidth, &mapHeight, &mapDepth);
	while(fscanf(fp, "%d,", &tile) != EOF)
		tileMatrix.emplace_back(tile);

	fclose(fp);

	LoadWallRects();
}

void TileMap::SetTileSet(TileSet *tileSet)
{
	this->tileSet = tileSet;
}

int TileMap::At(int x, int y, int z)
{
	int index = (z*mapWidth*mapHeight) + (mapWidth*y) + x;
	return tileMatrix.at(index);
}

void TileMap::Render(int cameraX, int cameraY)
{
	for (int i = 0; i < mapDepth; i++)
		RenderLayer(i, cameraX, cameraY);
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY)
{
	int tileWidth = tileSet->GetTileWidth();
	int tileHeight = tileSet->GetTileHeight();

	for (int i = 0; i < mapWidth; ++i)
		for (int j = 0; j < mapHeight; ++j)
		{
			tileSet->Render(At(i, j, layer), (i*tileWidth)-cameraX, (j*tileHeight)-cameraY);
			//Renders red, transparent boxes on top of the wall.
			if(HITBOX_MODE && (layer == 1) && (At(i, j, layer) > -1))
			{
				SDL_SetRenderDrawColor(Game::GetInstance()->GetRenderer(), 255, 0, 0, 200);
				SDL_SetRenderDrawBlendMode(Game::GetInstance()->GetRenderer(), SDL_BLENDMODE_BLEND);
				SDL_Rect rect;
				rect.x = (i*tileWidth)-cameraX;
				rect.y = (j*tileHeight)-cameraY;
				rect.w = tileWidth;
				rect.h = tileHeight;
				SDL_RenderFillRect(Game::GetInstance()->GetRenderer(), &rect);
			}
		}
}

int TileMap::GetWidth(void)
{
	return mapWidth;
}

int TileMap::GetHeight(void)
{
	return mapHeight;
}

int TileMap::GetDepth(void)
{
	return mapDepth;
}

void TileMap::LoadWallRects(void)
{
	int tileWidth = tileSet->GetTileWidth();
	int tileHeight = tileSet->GetTileHeight();

    for(int i = 0; i < mapWidth; i++)
	{
		for(int j = 0; j < mapHeight; j++)
		{
			if(At(i, j, 1) > -1)
			{
                wallRect.emplace_back(Vec2(i*tileWidth, j*tileHeight), Vec2(tileWidth, tileHeight));
			}
		}
	}
}

std::vector<Rect> TileMap::GetWallRect(void)
{
	return wallRect;
}
