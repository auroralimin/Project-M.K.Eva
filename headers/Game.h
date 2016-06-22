#pragma once
#include <stack>
#include <memory>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "State.h"

/***************************************************************************/ /**
  * Coordinates the game.
  * Initialize all necessary dependences of the game, as well as manages the
  *game
  * main loop.
  ******************************************************************************/
class Game
{
  public:
    /**
     * Quits and frees all dependencies and dinamically allocated variables.
     */
    ~Game(void);

    /**
     * Ensures that this class is a Singleton.
     * It garantees thet the game has at maximum one instance of Game at all
     * times by returning always the same instance.
     * @param title a string argument containing the game window title
     * @param w a int argument with the game window width
     * @param h a int argument with the game window height
     * @return Returns a poiter to the unique instance of Game class
     */
    static Game *GetInstance(std::string title, int w, int h);

    /**
     * Ensures that this class is a Singleton.
     * It garantees thet the game has at maximum one instance of Game at all
     * times by returning always the same instance.
     * @return Returns a pointer to the unique instance of Game class
     */
    static Game *GetInstance(void);

    /**
     * Gets the game SDL renderer.
     * @return Returns the pointer to the game SDL renderer
     */
    SDL_Renderer *GetRenderer(void);

    /**
     * Gets the game current state.
     * @return Returns a referance to game current state
     */
    State &GetCurrentState(void);

    /**
     * Push a new state to the game stack of states.
     * @param *state a State pointer to a new state to be pushed
     */
    void Push(State *state);

    /**
     * Starts running the game main loop.
     */
    void Run(void);

    /**
     * Gets the frame delta time.
     * @return Returns the game dt
     */
    int GetDeltaTime(void);

    /**
     * Gets the game window width.
     * @return Returns the game window width
     */
    int GetWinWidth(void);

    /**
     * Gets the game window height.
     * @return Returns the game window height
     */
    int GetWinHeight(void);

    /**
     * Clears the game renderer.
     */
    void ClearRenderer(void);

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
    void ClearResources(void);
};

