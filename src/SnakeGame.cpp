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

    // Run the game loop
    int gameResult = gameLoop();

    // Close SDL down
    closeSDL();

    return gameResult;
}

int SnakeGame::gameLoop()
{
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
                quit = true;
                break;
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

    // Offer chance to start over?
    quit = false;
    gameOver(gRenderer, std::to_string(mySnake.length * 10).c_str(),
        SCREEN_WIDTH, SCREEN_HEIGHT);

    while(!quit)
    {
        // Handle input
        while(SDL_PollEvent(&event) != 0)
        {
            onEvent(&event);
        }

        switch(lastKey)
        {
            case 5:
                quit = true;
                break;

            case 6:
                return gameLoop();
                break;
        }

        // Present the rendered frame
        SDL_RenderPresent(gRenderer);

        // 150ms delay = ~7 fps
        SDL_Delay(150);
    }

    return 0;
}


int SnakeGame::gameOver(SDL_Renderer* r, const char* s, int w, int h)
{
    TTF_Font* Sans = TTF_OpenFont(
        "/usr/share/fonts/truetype/liberation2/LiberationSans-Regular.ttf", 12);

    SDL_Color textColor = {255, 100, 100};

    const char* scoreBanner = "Score: ";
    const char* scoreTot = s;
    const char* again = "Play again? [y/n].";

    SDL_Surface* msg2 = TTF_RenderText_Solid(Sans, scoreBanner, textColor);
    SDL_Surface* msg3 = TTF_RenderText_Solid(Sans, scoreTot, textColor);
    SDL_Surface* msg4 = TTF_RenderText_Solid(Sans, again, textColor);

    SDL_Texture* tMsg2 = SDL_CreateTextureFromSurface(r, msg2);
    SDL_Texture* tMsg3 = SDL_CreateTextureFromSurface(r, msg3);
    SDL_Texture* tMsg4 = SDL_CreateTextureFromSurface(r, msg4);

    SDL_Rect msg_rect2;
    msg_rect2.x = w / 2 - 70;
    msg_rect2.y = h / 3;
    msg_rect2.w = 70;
    msg_rect2.h = 50;

    SDL_Rect msg_rect3;
    msg_rect3.x = w / 2 + 10;
    msg_rect3.y = h / 3;
    msg_rect3.w = 60;
    msg_rect3.h = 50;

    SDL_Rect msg_rect4;
    msg_rect4.x = w / 2 - 175;
    msg_rect4.y = h / 3 + 55;
    msg_rect4.w = 350;
    msg_rect4.h = 50;

    SDL_RenderCopy(r, tMsg2, NULL, &msg_rect2);
    SDL_RenderCopy(r, tMsg3, NULL, &msg_rect3);
    SDL_RenderCopy(r, tMsg4, NULL, &msg_rect4);

    SDL_FreeSurface(msg2);
    SDL_FreeSurface(msg3);
    SDL_FreeSurface(msg4);
    SDL_DestroyTexture(tMsg2);
    SDL_DestroyTexture(tMsg3);
    SDL_DestroyTexture(tMsg4);

    return 0;
}

int main(int argc, char** argv)
{
    SnakeGame snake = SnakeGame();

    return snake.onExecute();
}