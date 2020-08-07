#include "SnakeGame.h"        // SnakeGame struct and other includes

// Initialize SDL and create our window and generator
bool SnakeGame::initSDL()
{
    // Initialize SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Couldn't initialize SDL! Error: "
            << SDL_GetError() << "\n";
        return false;
    }

    // Initialize SDL_TTF
    if(TTF_Init() < 0)
    {
        std::cout <<"Couldn't initialize TTF! Error: "
            << TTF_GetError() << "\n";
    }

    // Create window
    gWindow = SDL_CreateWindow("SDL Snake", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(gWindow == NULL)
    {
        std::cout << "Error creating SDL window! Error: " << SDL_GetError()
            << "\n";
        return false;
    }

    // Create renderer
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if(gRenderer == NULL)
    {
        std::cout << "Error creating SDL renderer! Error: " << SDL_GetError()
            << "\n";
        return false;
    }
    else
    {
        // Black background
        SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0x0);
    }

    return true;
}

// Catch SDL events to handle a quit signal
void SnakeGame::onEvent(SDL_Event* e)
{
    // Clicking x
    if(e->type == SDL_QUIT)
    {
        quit = true;
    }

    if(e->type == SDL_KEYDOWN)
    {
        switch(e->key.keysym.sym)
        {
            case SDLK_SPACE:
            if(paused)
            {
                paused = false;
            }
            else
            {
                paused = true;
            }
            break;

            case SDLK_w:
                // Move up
                lastKey = UP;
                break;

            case SDLK_s:
                // Move down
                lastKey = DOWN;
                break;

            case SDLK_a:
                // Move left
                lastKey = LEFT;
                break;

            case SDLK_d:
                // Move right
                lastKey = RIGHT;
                break;

            case SDLK_n:
                // Quit
                lastKey = QUIT;
                break;

            case SDLK_y:
                // Play again
                lastKey = PLAY_AGAIN;
                break;
        }
    }
}

// Free up resources and close down the SDL systems
void SnakeGame::closeSDL()
{
    // Free up window and renderer
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    // Close out SDL TTF
    TTF_Quit();

    // Close out SDL subsystems
    SDL_Quit();
}