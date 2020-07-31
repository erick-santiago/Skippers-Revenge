/*
 * Birds.cpp
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#include "constants.h"
#include "globals.h"
#include <SDL2/SDL_mixer.h>
#include "Gunner.h"
#include "Bird.h"
#include "Birds.h"
#include "GamePlay.h"



RBird::RBird( int x, int y) 
    : Bird( x, y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;

    // initialize x-velocity
    mVelX = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to Rbird's offset
    shiftCollider();
}


void RBird::move( Gunner &gunner)
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();
    //std::cout << std::endl << " " << getmCollx();

    // if the bird went too far to the left 
    if( mPosX + BIRD_WIDTH < 0 ) 
    {
        delBird_flag = true;  
    }

    if( mVelX == 0 )
        mVelX = BIRD_XVEL;

}


void RBird::render( GamePlay &GP)
{
    // show the bird
	GP.gRBirdF2Texture.render( mPosX, mPosY );
}


void RBird::sfx_call()
{
    Mix_PlayChannel( -1, sfx_bPop2 , 0 );
    Mix_PlayChannel( -1, sfx_hCrow , 0 );
}


void RBird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int RBird::getmCollx()
{
    return mCollider.x;
}


int RBird::getmColly()
{
    return mCollider.y;
}


int RBird::getmCollw()
{
    return mCollider.w;
}


int RBird::getmCollh()
{
    return mCollider.h;
}


BBird::BBird( int x, int y) 
    : Bird( x, y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;

    // initialize x,y velocities
    mVelX = 0;
    mVelY = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to Bbird's offset
    shiftCollider();
}


void BBird::move( Gunner &gunner)
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();
    //std::cout << std::endl << " " << getmCollx();

    // if the bird went too far to the left 
    if( mPosX + BIRD_WIDTH < 0 ) 
    {
        delBird_flag = true;  
    }

    // move the bird along y-axis
    mPosY += mVelY;
    shiftCollider();

    // if the bird went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + BIRD_HEIGHT > SCREEN_HEIGHT ) )
    {
        mPosY -= mVelY; // move back
        mVelY *= -1;  // negate velocity
        mPosY += mVelY;
        shiftCollider();
    }

    if( mVelX == 0 )
    {    
        mVelX = BIRD_XVEL;
        mVelY = BIRD_YVEL;
    }

}


void BBird::render( GamePlay &GP)
{
    // show the bullet
	GP.gBBirdF3Texture.render( mPosX, mPosY );
}


void BBird::sfx_call()
{
    Mix_PlayChannel( -1, sfx_bPop2 , 0 );
    Mix_PlayChannel( -1, sfx_lCrow , 0 );
}


void BBird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int BBird::getmCollx()
{
    return mCollider.x;
}


int BBird::getmColly()
{
    return mCollider.y;
}


int BBird::getmCollw()
{
    return mCollider.w;
}


int BBird::getmCollh()
{
    return mCollider.h;
}


YBird::YBird( int x, int y) 
    : Bird( x, y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;

    // initialize x,y velocities
    mVelX = 0;
    mVelY = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to Bbird's offset
    shiftCollider();
}


void YBird::move(Gunner &gunner)
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();
    //std::cout << std::endl << " " << getmCollx();

    // if the bird went too far to the left 
    if( mPosX + BIRD_WIDTH < 0 ) 
    {
        delBird_flag = true;  
    }

    // move the bird along y-axis
    mPosY += mVelY;
    shiftCollider();

    // if the bird went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + BIRD_HEIGHT > SCREEN_HEIGHT ) )
    {
        mPosY -= mVelY; // move back
        mVelY *= -1;  // negate velocity
        mPosY += mVelY;
        shiftCollider();
    }

    if( mVelX == 0 )
    {    
        mVelX = BIRD_XVEL;
        mVelY = BIRD_YVEL;
    }

}


void YBird::render( GamePlay &GP)
{
    // show the bullet
	GP.gYBirdF1Texture.render( mPosX, mPosY );
}


void YBird::sfx_call()
{
    Mix_PlayChannel( -1, sfx_bPop2 , 0 );
    Mix_PlayChannel( -1, sfx_lCrow , 0 );
}


void YBird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int YBird::getmCollx()
{
    return mCollider.x;
}


int YBird::getmColly()
{
    return mCollider.y;
}


int YBird::getmCollw()
{
    return mCollider.w;
}


int YBird::getmCollh()
{
    return mCollider.h;
}


GBird::GBird( int x, int y) 
    : Bird( x, y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;

    // initialize x-velocity
    mVelX = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to Rbird's offset
    shiftCollider();
}


void GBird::move(Gunner &gunner)
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();
    //std::cout << std::endl << " " << getmCollx();

    // if the bird went too far to the left 
    if( mPosX + BIRD_WIDTH < 0 ) 
    {
        delBird_flag = true;  
    }

    if( mVelX == 0 )
        mVelX = BIRD_XVEL;

}


void GBird::render( GamePlay &GP)
{
    // show the bullet
	GP.gGBirdF2Texture.render( mPosX, mPosY );
}


void GBird::sfx_call()
{
    Mix_PlayChannel( -1, sfx_bPop2 , 0 );
    Mix_PlayChannel( -1, sfx_hCrow , 0 );
}

void GBird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int GBird::getmCollx()
{
    return mCollider.x;
}


int GBird::getmColly()
{
    return mCollider.y;
}


int GBird::getmCollw()
{
    return mCollider.w;
}


int GBird::getmCollh()
{
    return mCollider.h;
}


HBird::HBird( int x, int y) 
    : Bird( x, y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;

    // initialize x,y velocities
    mVelX = 0;
    mVelY = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to Bbird's offset
    shiftCollider();
}


void HBird::move( Gunner &gunner)
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();
    //std::cout << std::endl << " " << getmCollx();

    // if the bird went too far to the left 
    if( mPosX + BIRD_WIDTH < 0 ) 
    {
        delBird_flag = true;  
    }

    // move the bird along y-axis
    if( mPosY - gunner.getPosY() > 34 )
    {   
        mPosY -= mVelY;
        shiftCollider();
    }

    else if( mPosY - gunner.getPosY() < -32 )
    {
        mPosY += mVelY;
        shiftCollider();
    }

    else
    {
        mPosY += 0;
        shiftCollider();
    }

    // if the bird went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + BIRD_HEIGHT > SCREEN_HEIGHT ) )
    {
        mPosY -= mVelY; // move back
        mVelY *= -1;  // negate velocity
        mPosY += mVelY;
        shiftCollider();
    }

    if( mVelX == 0 )
    {    
        mVelX = BIRD_XVEL;
        mVelY = BIRD_YVEL;
    }

}


void HBird::render( GamePlay &GP)
{
    // show the bullet
	GP.gHBirdF1Texture.render( mPosX, mPosY );
}


void HBird::sfx_call()
{
    Mix_PlayChannel( -1, sfx_bPop2 , 0 );
    Mix_PlayChannel( -1, sfx_hCrow , 0 );
}


void HBird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int HBird::getmCollx()
{
    return mCollider.x;
}


int HBird::getmColly()
{
    return mCollider.y;
}


int HBird::getmCollw()
{
    return mCollider.w;
}


int HBird::getmCollh()
{
    return mCollider.h;
}





