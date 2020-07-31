/*
 * Gunner.h
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#ifndef GUNNER_H_
#define GUNNER_H_

#include <vector>
#include <memory>

class Bird;


//The gunner that will move around on the screen
class Gunner
{
    public:
		//The dimensions of the gunner
		static const int GUNNER_WIDTH = 101;
		static const int GUNNER_HEIGHT = 65;

		//Maximum axis velocity of the gunner
		static const int GUNNER_VEL = 5;

		//Initializes the variables
		Gunner();

		//Takes key presses and adjusts the gunner's velocity
		void handleEvent( SDL_Event& e );

		//Moves the gunner
		void move( std::vector< std::unique_ptr<Bird> > &spvect );

		//Shows the gunner on the screen
		void render();

        void sfx_call();

        bool hitGunner_flag;

        bool dedGunner_flag;

        int getPosX();

        int getPosY();

        bool bullet_flag; 

        bool bird_flag;

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

        void setPoints();

        Uint32 getPoints();

        void setHP();

        Uint32 getHP();

    private:
        // initial vertical offset
        int verticalOffset;

		//The X and Y offsets of the gunner
		int mPosX, mPosY;

		//The velocity of the gunner
		int mVelX, mVelY;

        // gunner's collision box
        SDL_Rect mCollider;

        // reposition coll box relative to gunner's offset
        void shiftCollider();

        // destroy points
        Uint32 points;

        // health points
        Uint32 hp;
};


#endif  // GUNNER_H_





