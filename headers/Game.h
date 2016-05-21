#pragma once
#include <stack>
#include <memory>

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
		State& GetCurrentState(void);
		void Push(State	*state);
		void Run(void);
		int GetDeltaTime(void);
		int GetWinWidth(void);
		int GetWinHeight(void);

	private:
		static Game *_instance;
		SDL_Window *window;
		SDL_Renderer *renderer;
		float dt;
		int frameStart, currentTime;
		int winWidth, winHeight;
		State *storedState;
		std::stack<std::unique_ptr<State>> stateStack;

		Game(std::string title, int w, int h);
		void CalculateDeltaTime(void);
};

