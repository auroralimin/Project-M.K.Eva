#include "InputManager.h"

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

	while (SDL_PollEvent(&event))
	{
		if (event.key.repeat == 1)
			continue;
	
		SDL_GetMouseState(&mouseX, &mouseY);
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

	keyUpdate[LEFT_ARROW_KEY] = keyUpdate[RIGHT_ARROW_KEY] = 0;
	keyState[LEFT_ARROW_KEY] = keyState[RIGHT_ARROW_KEY] = false;

	keyUpdate[UP_ARROW_KEY] = keyUpdate[DOWN_ARROW_KEY] = 0;
	keyState[UP_ARROW_KEY] = keyState[DOWN_ARROW_KEY] = false;

	keyUpdate[W_KEY] = keyUpdate[S_KEY] = 0;
	keyUpdate[A_KEY] = keyUpdate[D_KEY] = 0;

	keyState[W_KEY] = keyState[S_KEY] = false;
	keyState[A_KEY] = keyState[D_KEY] = false;
}

