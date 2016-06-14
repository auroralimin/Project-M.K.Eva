#include "InputManager.h"

InputManager& InputManager::GetInstance(void)
{
	static InputManager *_instance = new InputManager();
	return *_instance;
}

void InputManager::Update(void)
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

bool InputManager::KeyPress(int key)
{
	return (updateCounter == keyUpdate.find(key)->second) ?
		   keyState.find(key)->second : false;
}

bool InputManager::KeyRelease(int key)
{
	return (updateCounter == keyUpdate.find(key)->second) ?
		   !keyState.find(key)->second : false;
}

bool InputManager::IsKeyDown(int key)
{
	return keyState.find(key)->second;
}

bool InputManager::MousePress(int button)
{
	return (updateCounter == mouseUpdate[button]) ? mouseState[button] : false;
}

bool InputManager::MouseRelease(int button)
{
	return (updateCounter == mouseUpdate[button]) ? !mouseState[button] : false;
}

bool InputManager::IsMouseDown(int button)
{
	return mouseState[button];
}

int InputManager::GetMouseX(void)
{
	return mouseX;
}

int InputManager::GetMouseY(void)
{
	return mouseY;
}

bool InputManager::IsQuitRequested(void)
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

    keyUpdate[Q_KEY] = keyUpdate[E_KEY] = 0;
    keyState[Q_KEY] = keyState[E_KEY] = false;

	keyUpdate[H_KEY] = keyUpdate[J_KEY] = keyUpdate[K_KEY] = keyUpdate[L_KEY] = 0;
	keyState[H_KEY] = keyState[J_KEY] = keyState[K_KEY] = keyState[L_KEY] = false;

    keyUpdate[NUM_1_KEY] = keyUpdate[NUM_2_KEY] = keyUpdate[NUM_3_KEY] = 0;
    keyState[NUM_1_KEY] = keyState[NUM_2_KEY] = keyState [NUM_3_KEY] = false;
}

