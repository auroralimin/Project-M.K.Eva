#include "InputManager.h"
#include "SDL2/SDL.h"

InputManager& InputManager::getInstance(void)
{
	static InputManager *_instance = new InputManager();
	return *_instance;
}

void InputManager::update(void)
{
    SDL_Event event;

	quitRequested = false;
	updateCounter++;
	SDL_GetMouseState(&mouseX, &mouseY);

	while (SDL_PollEvent(&event))
	{
		if (event.key.repeat == 1)
			continue;
	
		switch(event.type)
		{
			case SDL_QUIT:
				quitRequested = true;
				break;

			case SDL_KEYDOWN:
				keyState[event.key.keysym.sym] = true;
				keyUpdate[event.key.keysym.sym] = updateCounter;
				break;

			case SDL_KEYUP:
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
				break;

			case SDL_MOUSEBUTTONUP:
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
				break;

			default:
				//Do nothing
				break;
		}
	}

	if (SDL_QuitRequested())
		quitRequested = true;
}

bool InputManager::keyPress(int key)
{
	return (updateCounter == keyUpdate.find(key)->second) ?
		   keyState.find(key)->second : false;
}

bool InputManager::keyRelease(int key)
{
	return (updateCounter == keyUpdate.find(key)->second) ?
		   !keyState.find(key)->second : false;
}

bool InputManager::isKeyDown(int key)
{
	return keyState.find(key)->second;
}

bool InputManager::mousePress(int button)
{
	return (updateCounter == mouseUpdate[button]) ? mouseState[button] : false;
}

bool InputManager::mouseRelease(int button)
{
	return (updateCounter == mouseUpdate[button]) ? !mouseState[button] : false;
}

bool InputManager::isMouseDown(int button)
{
	return mouseState[button];
}

int InputManager::getMouseX(void)
{
	return mouseX;
}

int InputManager::getMouseY(void)
{
	return mouseY;
}

bool InputManager::isQuitRequested(void)
{
	return quitRequested;
}

/*
 * PRIVATE METHODS
 */
InputManager::InputManager(void) : quitRequested(false),
								   mouseState{false},
								   mouseUpdate{0},
								   updateCounter(0)
{
	keyUpdate[ESCAPE_KEY] = keyUpdate[SPACEBAR] = 0;
	keyState[ESCAPE_KEY] = keyState[SPACEBAR] = false;
}

