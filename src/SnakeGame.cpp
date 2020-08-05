#include "snake.h"
#include "SnakeGame.h"
#include "food.h"

int SnakeGame::onExecute()
{
    // Init SDL
    gRenderer = nullptr;
    gWindow = nullptr;
    if(!initSDL())
    {
        std::cout << "Failed to initialize SDL.\n";
        return -1;
    }

    // Prepare for main loop
    quit = false;
    paused = false;
    SDL_Event event;
    lastKey = 0;

    // Initialize some classes
    Snake mySnake = Snake(SCREEN_HEIGHT, SCREEN_WIDTH);
    Food myFood = Food(SCREEN_HEIGHT, SCREEN_WIDTH, mySnake.scl);

    // Start main loop
    while(!quit)
    {
        // Handle input
        while(SDL_PollEvent(&event) != 0)
        {
            onEvent(&event);
        }

        // Advance game if it's not paused
        if(!paused)
        {
            // Reset renderer for the next frame
            SDL_SetRenderDrawColor(gRenderer, 0x0, 0x0, 0x0, 0xFF);
            SDL_RenderClear(gRenderer);

            // Snake contact?
            if(mySnake.die())
            {
                std::cout << "Your snake died!\n" << "Your score: " << mySnake.length * 10 << "\n";
                quit = true;
            }

            // Put the food out there
            myFood.show(gRenderer, mySnake.scl);

            // Draw my snakey to the screen
            mySnake.show(gRenderer);

            // Check for snake eat food
            if(mySnake.eat(myFood.x, myFood.y))
            {
                myFood = Food(SCREEN_HEIGHT, SCREEN_WIDTH, mySnake.scl);
            }

            // Movement commands
            mySnake.dir(lastKey);

            // Update snake's location for the next frame
            mySnake.update();
        }

        // Present the rendered frame
        SDL_RenderPresent(gRenderer);

        // 150ms delay = ~7 fps
        SDL_Delay(150);
    }

    // Close SDL down
    closeSDL();

    return 0;
}

int main(int argc, char** argv)
{
    SnakeGame snake = SnakeGame();

    return snake.onExecute();
}