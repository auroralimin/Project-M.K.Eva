#include "Minimap.h"

#define MINIMAP_X 900
#define MINIMAP_Y 5

Minimap::Minimap(std::string file) : sp(file)
{
    sp.SetScaleX(8);
    sp.SetScaleY(3);
}

void Minimap::Render()
{
    sp.Render(MINIMAP_X, MINIMAP_Y);
}
