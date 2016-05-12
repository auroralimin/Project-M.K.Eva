#pragma once

class Timer
{
	public:
		Timer();
		void update(float dt);
		void restart(void);
		float get(void);

	private:
		float time;
};

