#include <SDL2/SDL.h>           // SDL libs
#include <math.h>               // abs()
#include <list>                 // mutable list
#include <iostream>

struct Snake
{
    int x;
    int y;
    int xspeed;
    int yspeed;
    int scl;
    int length;
    std::list<int> tailX;
    std::list<int> tailY;

    int screenHeight;
    int screenWidth;

    Snake() {}

    Snake(int screenHeight, int screenWidth)
    {
        this->x = 0;
        this->y = 0;
        this->xspeed = 1;
        this->yspeed = 0;
        this->scl = 20;
        this->length = 0;

        this->screenHeight = screenHeight;
        this->screenWidth = screenWidth;
    }

    void dir(int lastKey)
    {
        switch (lastKey)
        {
            case 1:
                if(this->yspeed == 0 && this->x % this->scl == 0)
                {
                    this->xspeed = 0;
                    this->yspeed = -1;
                    lastKey = 0;
                }
                break;
            
            case 2:
                if(this->yspeed == 0 && this->x % this->scl == 0)
                {
                    this->xspeed = 0;
                    this->yspeed = 1;
                    lastKey = 0;
                }
                break;

            case 3:
                if(this->xspeed == 0 && this->y % this->scl == 0)
                {
                    this->xspeed = -1;
                    this->yspeed = 0;
                    lastKey = 0;
                }
                break;

            case 4:
                if(this->xspeed == 0 && this->y % this->scl == 0)
                {
                    this->xspeed = 1;
                    this->yspeed = 0;
                    lastKey = 0;
                }
                break;
        }
    }

    void update()
    {
        // Add last position to tail list
        if(this->x % this->scl == 0 && this->y % this->scl == 0)
        {
            tailX.push_front(this->x);
            tailY.push_front(this->y);
        }

        this->x += this->xspeed * this->scl;
        this->y += this->yspeed * this->scl;
    }

    void show(SDL_Renderer* r)
    {
        SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);

        // Draw current snake position
        SDL_Rect mySnake;
        mySnake.x = this->x;
        mySnake.y = this->y;
        mySnake.w = this->scl;
        mySnake.h = this->scl;

        SDL_RenderFillRect(r, &mySnake);

        // Draw snake length
        auto itX = this->tailX.begin();
        auto itY = this->tailY.begin();
        for(int i = 0; i < this->length; i++)
        {
            SDL_Rect tailPiece;
            tailPiece.x = *itX;
            tailPiece.y = *itY;
            tailPiece.w = this->scl;
            tailPiece.h = this->scl;

            SDL_RenderFillRect(r, &tailPiece);
            itX = std::next(itX, 1);
            itY = std::next(itY, 1);
        }
    }

    bool eat(int x, int y)
    {
        if(abs(this->x - x) < this->scl && abs(this->y - y) < this->scl)
        {
            this->length++;
            return true;
        }

        return false;
    }

    bool die()
    {
        // Check for wall collision first
        if(this->x > this->screenWidth - scl || this->x < 0)
        {
            return true;
        }

        if(this->y > this->screenHeight - scl || this->y < 0)
        {
            return true;
        }

        // Check for body collision
        auto itX = this->tailX.begin();
        auto itY = this->tailY.begin();
        for(int i = 0; i < this->length; i++)
        {
            int thisX = *itX;
            int thisY = *itY;
            std::cout << "HeadX: " << this->x << "\nHeadY: " << this->y;
            std::cout << "\nTailX: " << thisX << "\nTailY: " << thisY << "\n\n";
            if(abs(this->x - thisX) < this->scl && abs(this->y - thisY) < this->scl)
            {
                return true;
            }
            itX = std::next(itX, 1);
            itY = std::next(itY, 1);
        }

        return false;
    }
};