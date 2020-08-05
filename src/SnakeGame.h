#include <SDL2/SDL.h>       // SDL libraries
#include <random>           // Random libraries
#include <iostream>         // Write to console and maybe something else, who knows
#include <time.h>           // time() for simple initialization of random
#include <sys/types.h>      // fork()?
#include <unistd.h>         // fork()?

#define SCREEN_WIDTH        600
#define SCREEN_HEIGHT       600

struct SnakeGame
{
public:
    int onExecute();
    bool initSDL();
    void onEvent(SDL_Event* e);
    void closeSDL();

    bool quit;
    bool paused;

    int lastKey;

    SDL_Renderer* gRenderer;
    SDL_Window* gWindow;

    enum
    {
        UP = 1,
        DOWN,
        LEFT,
        RIGHT
    };
};