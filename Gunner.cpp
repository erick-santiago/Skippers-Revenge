/*
 * Gunner.cpp
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "Bird.h"
#include "Bullet.h"
#include "Gunner.h"
#include "GamePlay.h"


Gunner::Gunner()
    : bullet_flag( false ), bird_flag( false ), hitGunner_flag( false ), dedGunner_flag( false )
{
    //Initialize the offsets
    verticalOffset = rand() % 620;
    mPosX = 0;
    mPosY = verticalOffset;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    // initialize collision box
    mCollider.w = GUNNER_WIDTH;
    mCollider.h = GUNNER_HEIGHT;

    // initialize points
    points = 0;
    hp = 3;

    // reposition coll box relative to gunner's offset
    shiftCollider();
}

void Gunner::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= GUNNER_VEL; break;
            case SDLK_DOWN: mVelY += GUNNER_VEL; break;
            case SDLK_LEFT: mVelX -= GUNNER_VEL; break;
            case SDLK_RIGHT: mVelX += GUNNER_VEL; break;
        }

        // shoot bullet
        switch( e.key.keysym.sym )
        {
            case SDLK_d: bullet_flag = true; break;
        }

        // create bird
        switch( e.key.keysym.sym )
        {
            case SDLK_b: bird_flag = true; break;
        }

    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += GUNNER_VEL; break;
            case SDLK_DOWN: mVelY -= GUNNER_VEL; break;
            case SDLK_LEFT: mVelX += GUNNER_VEL; break;
            case SDLK_RIGHT: mVelX -= GUNNER_VEL; break;
        }
    }
}

void Gunner::move( std::vector< std::unique_ptr<Bird> > &spvect)
{
    //Move the gunner left or right
    mPosX += mVelX;
    shiftCollider();

    // check if gunner collided with bird
    if( checkCollisionGBx( *this, spvect ) )
    {
        //delBird_flag = true;
        //Move back
        mPosX -= mVelX;
        shiftCollider();
    }

    //If the gunner went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + GUNNER_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
        shiftCollider();
    }

    //Move the gunner up or down
    mPosY += mVelY;
    shiftCollider();

    // if gunner collided with bird
    if( checkCollisionGBx( *this, spvect ) )
    {
        //delBird_flag = true;
        //Move back
        mPosY -= mVelY;
        shiftCollider();
    }

    //If the gunner went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + GUNNER_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
        shiftCollider();
    }
}

void Gunner::render()
{
    //Show the gunner
	gGunnerTexture.render( mPosX, mPosY );
}

void Gunner::sfx_call()
{
    Mix_PlayChannel( -1, sfx_gHit , 0 );
}


int Gunner::getPosX()
{
    return mPosX;
}


int Gunner::getPosY()
{
    return mPosY;
}


void Gunner::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int Gunner::getmCollx()
{
    return mCollider.x;
}


int Gunner::getmColly()
{
    return mCollider.y;
}


int Gunner::getmCollw()
{
    return mCollider.w;
}


int Gunner::getmCollh()
{
    return mCollider.h;
}

void Gunner::setPoints()
{
    points += 10;
}

void Gunner::setHP()
{
    if( hp != 0 )
        hp -= 1;
    if( hp <= 0 )
        dedGunner_flag = true;
}

Uint32 Gunner::getPoints()
{
    return points;
}

Uint32 Gunner::getHP()
{
    return hp;
}
