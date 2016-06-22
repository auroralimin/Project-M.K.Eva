#include "HealthBar.h"

HealthBar::HealthBar(std::string baseFile, std::string overlayFile) :
    base(baseFile),
    bar("sprites/hud/healthbar/HEALTHBAR.png"),
    overlay(overlayFile)
{
}

void HealthBar::Render()
{
    base.Render();
    bar.Render(132);
    overlay.Render();
}

void HealthBar::Update(float hp)
{
    if (hp < 0)
        hp = 0;
    bar.SetScaleX(hp/100);
}
