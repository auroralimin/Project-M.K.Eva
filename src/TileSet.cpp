#include "TileSet.h"
#include <iostream>

TileSet::TileSet(int tileWidth, int tileHeight, std::string file) :
	tileSet(file), tileWidth(tileWidth), tileHeight(tileHeight)
{
	rows = tileSet.getHeight()/tileHeight;
	cols = tileSet.getWidth()/tileWidth;
}

void TileSet::render(int index, float x, float y)
{
	if ((index < rows*cols) && (index >= 0))
	{
		tileSet.setClip(((index-1)%cols)*tileWidth, ((index-1)/cols)*tileHeight,
				tileWidth, tileHeight);
		tileSet.render(x, y, 0.0);
	}
}

int TileSet::getTileWidth(void)
{
	return tileWidth;
}

int TileSet::getTileHeight(void)
{
	return tileHeight;
}

