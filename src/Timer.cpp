#include "Timer.h"

Timer::Timer() : time(0.0)
{
}

void Timer::Update(float dt)
{
    time += dt;
}

void Timer::Restart(void)
{
    time = 0.0;
}

float Timer::Get(void)
{
    return time;
}

