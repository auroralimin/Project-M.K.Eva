#pragma once
#include "SDL2/SDL.h"
#include <iostream>
#include <unordered_map>
/** @file InputManager.h */

/** \def LEFT_ARROW_KEY keyboard left arrow. */
#define LEFT_ARROW_KEY SDLK_LEFT

/** \def RIGHT_ARROW_KEY keyboard right arrow. */
#define RIGHT_ARROW_KEY SDLK_RIGHT

/** \def UP_ARROW_KEY keyboard up arrow. */
#define UP_ARROW_KEY SDLK_UP

/** \def DOWN_ARROW_KEY keyboard down arrow. */
#define DOWN_ARROW_KEY SDLK_DOWN

/** \def ESCAPE_KEY keyboard ESC. */
#define ESCAPE_KEY SDLK_ESCAPE

/** \def LEFT_MOUSE_BUTTON mouse left button. */
#define LEFT_MOUSE_BUTTON SDL_BUTTON_LEFT

/** \def RIGHT_MOUSE_BUTTON mouse right button. */
#define RIGHT_MOUSE_BUTTON SDL_BUTTON_RIGHT

/** \def SPACEBAR keyboard spacebar*/
#define SPACEBAR SDLK_SPACE

/** \def A_KEY keyboard a key */
#define A_KEY SDLK_a

/** \def S_KEY keyboard s key. */
#define S_KEY SDLK_s

/** \def W_KEY keyboard w key. */
#define W_KEY SDLK_w

/** \def D_KEY keyboard d key. */
#define D_KEY SDLK_d

/** \def H_KEY keyboard h key. */
#define H_KEY SDLK_h

/** \def J_KEY keyboard j key. */
#define J_KEY SDLK_j

/** \def K_KEY keyboard k key */
#define K_KEY SDLK_k

/** \def L_KEY keyboard l key */
#define L_KEY SDLK_l

/** \def NUM_1_KEY keyboard number 1 key */
#define NUM_1_KEY SDLK_1

/** \def NUM_2_KEY keyboard number 2 key */
#define NUM_2_KEY SDLK_2

/** \def NUM_3_KEY keyboard number 3 key */
#define NUM_3_KEY SDLK_3

/** \def Q_KEY keyboard Q key */
#define Q_KEY SDLK_q

/** \def E_KEY keyboard E key */
#define E_KEY SDLK_e

#define DEADZONE 8000

/***************************************************************************/ /**
  * This class manages the game input.
  ******************************************************************************/
class InputManager
{
  public:
    /**
     * Ensures that this class is a Singleton.
     * Thus, it returns always the same instance.
     * @return Returns a poiter to the unique instance of InputManager class
     */
    static InputManager &GetInstance(void);

    /**
     * Updates and process SDL input from keyborad and mouse.
     */
    void Update(void);

    /**
     * Checks if a given key was pressed.
     * @param key a int containing the key value
     * @return If the key was pressed
     */
    bool KeyPress(int key);

    /**
     * Checks if a given key was released.
     * @param key a int containing the key value
     * @return If the key was released
     */
    bool KeyRelease(int key);

    /**
     * Checks if a given key is being pressed.
     * @param key a int containing the key value
     * @return If the key is currently being pressed.
     */
    bool IsKeyDown(int key);

    /**
     * Checks if a given mouse button was pressed.
     * @param button a int containing the mouse button value
     * @return If the key was pressed
     */
    bool MousePress(int button);

    /**
     * Checks if a given mouse button was released.
     * @param button a int containing the mouse button value
     * @return If the mouse button was released.
     */
    bool MouseRelease(int button);

    /**
     * Checks if a given mouse button is being pressed.
     * @param button a int containing the mouse button value
     * @return If the mouse button is currently being pressed
     */
    bool IsMouseDown(int button);

    /**
     * Gets the mouse x position.
     * @return Returns x position of the mouse
     */
    int GetMouseX(void);

    /**
     * Gets the mouse y position.
     * @return Returns y position of the mouse
     */
    int GetMouseY(void);

    /**
     * Checks if SDL input received a quit signal.
     * @return Returns if the input requested quit
     */
    bool IsQuitRequested(void);

  private:
    InputManager(void);
    bool AddController(int id);
    void RemoveController(void);
    void handleAxis(SDL_ControllerAxisEvent axis);

    bool quitRequested;
    bool mouseState[5];
    int mouseUpdate[5];
    int updateCounter;
    int mouseX, mouseY;
    std::unordered_map<int, bool> keyState;
    std::unordered_map<int, int> keyUpdate;
    std::unordered_map<int, int> joy2Key;
    SDL_GameController *gameController;
};
