#ifndef BULLET_H_   
#define BULLET_H_

#include <SDL2/SDL.h>
#include <vector>

class Bird;


class Bullet
{
    public:
        // the dimensions of the bullet
        static const int BULLET_WIDTH = 50;
        static const int BULLET_HEIGHT = 20;

        // max horizontal velocity of the bullet
        static const int BULLET_VEL = 8;

        // initializes the variables
        Bullet( int x, int y);

        // moves the bullet
        void move( std::vector< std::unique_ptr<Bird> > &spvect);

        // shows the bullet on the screen
        void render();

        bool delBullet_flag;

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

    private:
        // the X and Y offsets of the bullet
        int mPosX, mPosY;
 
        // the x velovity of the bullet
        int mVelX; 

        // bullet's collision box
        SDL_Rect mCollider;

        // reposition coll box relative to bullet's offset
        void shiftCollider();       
};


#endif  // BULLET_H_
