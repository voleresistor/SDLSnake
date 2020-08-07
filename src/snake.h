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

    // Some gross switch stuff to handle the controls
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

    /*
        Update the snake head location. We're keeping frame rates low and just
        updating each movement by a full scale jump. This makes snake
        movement jerkier, but prevents us from needing to animate each tail
        piece to keep the end of the tail from flickering.
    */
    void update()
    {
        // Add last position to tail list
        if(this->x % this->scl == 0 && this->y % this->scl == 0)
        {
            this->tailX.push_front(this->x);
            this->tailY.push_front(this->y);
        }

        /*
            Trim the tail list.
            If we don't do this then the list grows forever. That's
            probably not a big deal in a game like this, but there's no reason
            not to develop good habits right now.
        */
        //std::cout << "Trimming " << (this->tailX.size() - this->length)
        //    << " entries from TailX and TailY.\n";
        if(this->tailX.size() - this->length > 0)
        {
            this->tailX.pop_back();
            this->tailY.pop_back();
        }

        // Update the snake location
        this->x += this->xspeed * this->scl;
        this->y += this->yspeed * this->scl;
    }

    // Draw the snake head and tail to the renderer
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

        // Draw snake tail
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

    // Check to see if the snake head has intersected the food
    bool eat(int x, int y)
    {
        if(abs(this->x - x) < this->scl && abs(this->y - y) < this->scl)
        {
            this->length++;
            return true;
        }

        return false;
    }

    // Check to see if the snake head has intersected the tail or a boundary.
    bool die()
    {
        // Check for wall collision
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
            //std::cout << "HeadX: " << this->x << "\nHeadY: " << this->y;
            //std::cout << "\nTailX: " << thisX << "\nTailY: " << thisY << "\n\n";
            if(abs(this->x - thisX) < this->scl && abs(this->y - thisY)
                < this->scl)
            {
                return true;
            }
            itX = std::next(itX, 1);
            itY = std::next(itY, 1);
        }

        return false;
    }
};