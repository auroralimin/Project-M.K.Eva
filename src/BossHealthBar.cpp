#include "BossHealthBar.h"

#define BAR_POSITION_X 250
#define BAR_POSITION_Y 660
BossHealthBar::BossHealthBar() : bar("sprites/boss/BOSS-HEALTHBAR.png")
{
}

void BossHealthBar::Render()
{
    bar.Render(BAR_POSITION_X, BAR_POSITION_Y);
}

void BossHealthBar::Update(float hp)
{
    if (hp < 0)
        hp = 0;
    bar.SetClip(0, 0, bar.GetWidth() * hp / 500, bar.GetHeight());
}

