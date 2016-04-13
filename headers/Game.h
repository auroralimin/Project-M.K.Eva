#pragma once
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "State.h"

class Game
{
	public:
		~Game(void);
		static Game* getInstance(std::string title, int w, int h);
		static Game* getInstance(void);
		SDL_Renderer* getRenderer(void);
		State& getState(void);
		void run(void);

	private:
		static Game *_instance;
		State *state;
		SDL_Window *window;
		SDL_Renderer *renderer;

		Game(std::string title, int w, int h);
};

