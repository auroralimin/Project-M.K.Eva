#include "TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) :
	tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight)
{
	rows = tileSet.GetHeight()/tileHeight;
	cols = tileSet.GetWidth()/tileWidth;
}

void TileSet::Render(int index, float x, float y)
{
	if ((index < rows*cols) && (index >= 0))
	{
		tileSet.SetClip((index%cols)*tileWidth, (index/cols)*tileHeight,
				tileWidth, tileHeight);
		tileSet.Render(x, y, 0.0);
	}
}

int TileSet::GetTileWidth(void)
{
	return tileWidth;
}

int TileSet::GetTileHeight(void)
{
	return tileHeight;
}

