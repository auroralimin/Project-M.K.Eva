#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "State.h"

class Game
{
	public:
		~Game(void);
		static Game* GetInstance(std::string title, int w, int h);
		static Game* GetInstance(void);
		SDL_Renderer* GetRenderer(void);
		State& GetState(void);
		void Run(void);
		int GetDeltaTime(void);
		int GetWinWidth(void);
		int GetWinHeight(void);

	private:
		static Game *_instance;
		State *state;
		SDL_Window *window;
		SDL_Renderer *renderer;
		int frameStart, currentTime;
		int dt, winWidth, winHeight;

		Game(std::string title, int w, int h);
		void CalculateDeltaTime(void);
};

