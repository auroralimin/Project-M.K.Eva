#pragma once

class Timer
{
	public:
		Timer();
		void Update(float dt);
		void Restart(void);
		float Get(void);

	private:
		float time;
};

