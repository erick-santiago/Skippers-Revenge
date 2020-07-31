/*
 * Bird.h
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#ifndef BIRD_H_
#define BIRD_H_

#include <SDL2/SDL.h>

class GamePlay;
class Gunner;

//  Abstract Bird class
class Bird
{
    public:
        // the dimensions of the bird
        const int BIRD_WIDTH = 78;
        const int BIRD_HEIGHT = 48;

        // max horizontal velocity of the bird
        const int BIRD_XVEL = 5;

        // default constructor
        Bird();

        // initializes the variables
        Bird( int x, int y);

        // moves the bird
        virtual void move( Gunner &gunner) = 0;  // makes this an Abstract class

        // shows the bird on the screen
        virtual void render( GamePlay &GP);

        virtual void sfx_call();

        bool delBird_flag;

        bool hitBird_flag;

        virtual int getmCollx();  // left off here... made these methods virtual.. same as move() for correct implementation

        virtual int getmColly();

        virtual int getmCollw();
 
        virtual int getmCollh();

    protected:
        // the X and Y offsets of the bird
        int mPosX, mPosY;
 
        // the x and y velocity of the bird
        int mVelX, mVelY;

        // bird's collision box
        SDL_Rect mCollider;

        // reposition coll box relative to bird's offset
        virtual void shiftCollider();
};


#endif  // BIRD_H_
