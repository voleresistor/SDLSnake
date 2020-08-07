#include <SDL2/SDL.h>       // SDL libraries
#include <random>           // Random libraries
#include <iostream>         // Write to console and maybe something else, who knows
#include <time.h>           // time() for simple initialization of random
#include <SDL2/SDL_ttf.h>
#include <string>

#define SCREEN_WIDTH        600
#define SCREEN_HEIGHT       600

struct SnakeGame
{
public:
    int onExecute();
    int gameLoop();
    int gameOver(SDL_Renderer* r, const char* s, int w, int h);
    bool initSDL();
    void onEvent(SDL_Event* e);
    void closeSDL();

    bool quit;
    bool paused;

    int lastKey;

    SDL_Renderer* gRenderer;
    SDL_Window* gWindow;

    /*
        Directions are indexed from 1 so we can set lastKey to 0 between
        key presses.
    */
    enum
    {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT,
        QUIT,
        PLAY_AGAIN
    };
};