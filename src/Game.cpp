#include "Game.h"
#include "Camera.h"
#include "Config.h"
#include "InputManager.h"
#include "Resources.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <iostream>
#include <string>

#define FPS 60
#define FRAME_TIME 1000 / FPS

Game *Game::_instance = nullptr;

/*
 * PUBLIC METHODS
 */
Game::~Game(void)
{
    if (storedState != nullptr)
        delete storedState;
    while (!stateStack.empty())
        stateStack.pop();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    TTF_Quit();
    Mix_Quit();
    Mix_CloseAudio();
}

Game *Game::GetInstance(std::string title, int w, int h)
{
    if (!_instance)
        _instance = new Game(title, w, h);
    return _instance;
}

Game *Game::GetInstance(void)
{
    return _instance;
}

SDL_Renderer *Game::GetRenderer(void)
{
    return renderer;
}

State &Game::GetCurrentState(void)
{
    return *stateStack.top();
}

void Game::Push(State *state)
{
    storedState = state;
}

void Game::Run(void)
{
    if (storedState == nullptr) {
        ClearResources();
        return;
    }

    stateStack.emplace(storedState);
    storedState = nullptr;

    Camera::pos = Vec2(-SCREEN_PADDING / 2, -SCREEN_PADDING / 2);
    frameStart = SDL_GetTicks();
    while (!stateStack.empty()) {
        currentTime = SDL_GetTicks();
        CalculateDeltaTime();

        // Update and render top state from stack if quit not requested
        if (!stateStack.top()->IsQuitRequested()) {
            InputManager::GetInstance().Update();
            stateStack.top()->Update(dt);
            stateStack.top()->Render();
            SDL_RenderPresent(renderer);
        }

        // Checks if quit/pop was requested after update
        if (stateStack.top()->IsPopRequested() ||
            stateStack.top()->IsQuitRequested()) {
            stateStack.pop();
            if (!stateStack.empty())
                stateStack.top()->Resume();
        }

        if (storedState != nullptr) {
            stateStack.emplace(storedState);
            storedState = nullptr;
        }

        SDL_Rect rect;
        rect.x = Camera::pos.x;
        rect.y = Camera::pos.y;
        rect.w = winWidth;
        rect.h = winHeight;
        SDL_Renderer *renderer = Game::GetInstance()->GetRenderer();
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderFillRect(renderer, &rect);

        if (dt < FRAME_TIME)
            SDL_Delay(FRAME_TIME - dt);
        frameStart = currentTime;
    }
    ClearResources();
}

int Game::GetWinWidth(void)
{
    return winWidth;
}

int Game::GetWinHeight(void)
{
    return winHeight;
}

void Game::ClearRenderer(void)
{
    SDL_RenderClear(renderer);
}

/*
 * PRIVATE METHODS
 */
Game::Game(std::string title, int w, int h)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER |
                 SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER) < 0) {
        std::cerr << "Unable to init SDL: " << SDL_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (Mix_Init(MIX_INIT_OGG) < 0) {
        std::cerr << "Unable to init Mix_Music: " << Mix_GetError()
                  << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT,
                      MIX_DEFAULT_CHANNELS, 1024) == -1) {
        std::cerr << "Unable to open audio: " << Mix_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (TTF_Init() == -1) {
        std::cerr << "Unable to init TFF: " << TTF_GetError() << std::endl;
        exit(EXIT_SUCCESS);
    }

    if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) == 0) {
        std::cerr << "Unable to init SDL_Image: " << SDL_GetError()
                  << std::endl;
        exit(EXIT_SUCCESS);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED, w, h, 0);
    if (!window) {
        std::cerr << "Failed to create a window: " << SDL_GetError()
                  << std::endl;
        exit(EXIT_SUCCESS);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cerr << "Failed to create a renderer: " << SDL_GetError()
                  << std::endl;
        exit(EXIT_SUCCESS);
    }

    winWidth = w, winHeight = h;
    storedState = nullptr;
}

void Game::CalculateDeltaTime(void)
{
    dt = currentTime - frameStart;
}

void Game::ClearResources(void)
{
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
    Resources::ClearFonts();
}

