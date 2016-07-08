#pragma once
#include "Sprite.h"

class BossHealthBar
{
public:
    BossHealthBar();

    void Render();

    void Update(float hp);

private:
    Sprite bar;
};
