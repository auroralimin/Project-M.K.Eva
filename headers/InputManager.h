#pragma once
#include <iostream>
#include <unordered_map>
#include "SDL2/SDL.h"

#define LEFT_ARROW_KEY SDLK_LEFT
#define RIGHT_ARROW_KEY SDLK_RIGHT
#define UP_ARROW_KEY SDLK_UP
#define DOWN_ARROW_KEY SDLK_DOWN
#define ESCAPE_KEY SDLK_ESCAPE
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT
#define SPACEBAR SDLK_SPACE
#define A_KEY SDLK_a
#define S_KEY SDLK_s
#define W_KEY SDLK_w
#define D_KEY SDLK_d

class InputManager
{
	public:
		static InputManager& GetInstance(void);
		void Update(void);
		bool KeyPress(int key);
		bool KeyRelease(int key);
		bool IsKeyDown(int key);
		bool MousePress(int button);
		bool MouseRelease(int button);
		bool IsMouseDown(int button);
		int GetMouseX(void);
		int GetMouseY(void);
		bool IsQuitRequested(void);
	private:
		InputManager(void);

		bool quitRequested;
		bool mouseState[5];
		int mouseUpdate[5];
		int updateCounter;
		int mouseX, mouseY;
		std::unordered_map<int, bool> keyState;
		std::unordered_map<int, int> keyUpdate;
};

