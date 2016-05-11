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
		static InputManager& getInstance(void);
		void update(void);
		bool keyPress(int key);
		bool keyRelease(int key);
		bool isKeyDown(int key);
		bool mousePress(int button);
		bool mouseRelease(int button);
		bool isMouseDown(int button);
		int getMouseX(void);
		int getMouseY(void);
		bool isQuitRequested(void);
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

