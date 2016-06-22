#pragma once

#include "Sprite.h"
#include "Vec2.h"

class HealthBar
{
public:
    HealthBar(std::string baseFile, std::string overlayFile);

    void Render();

    void Update(float hp);

private:
    Sprite base;
    Sprite bar;
    Sprite overlay;
};



