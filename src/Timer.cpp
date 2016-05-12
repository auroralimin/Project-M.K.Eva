#include "Timer.h"

Timer::Timer() : time(0.0) {}

void Timer::update(float dt)
{
	time += dt;
}

void Timer::restart(void)
{
	time = 0.0;
}

float Timer::get(void)
{
	return time;
}

