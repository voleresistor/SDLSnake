#include <SDL2/SDL.h>

struct Food
{
public:
    int x;
    int y;

    int randX;
    int randY;

    Food() {}

    Food(int screenHeight, int screenWidth, int scl)
    {
        int cols = screenWidth / scl;
        int rows = screenHeight / scl;

        std::mt19937 gen(time(NULL));
        std::uniform_int_distribution<int> randX(0, cols - 1);
        std::uniform_int_distribution<int> randY(0, rows - 1);

        this->x = randX(gen) * scl;
        this->y = randY(gen) * scl;

        std::cout << "FoodX: " << this->x << "\nFoodY: " << this->y << "\n\n";
    }

    void show(SDL_Renderer* r, int scl)
    {
        SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0xA0, 0xFF);
        SDL_Rect snakeFood;
        snakeFood.x = this->x;
        snakeFood.y = this->y;
        snakeFood.h = scl;
        snakeFood.w = scl;

        SDL_RenderFillRect(r, &snakeFood);
    }
};