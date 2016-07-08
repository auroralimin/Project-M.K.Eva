#pragma once

#include "Sprite.h"

class Minimap
{
public:
    Minimap(std::string file);

    void Render();

private:
    Sprite sp;
};
