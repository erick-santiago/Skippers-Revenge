#include <SDL2/SDL.h>
#include "Gunner.h"
#include "GamePlay.h"
#include "Bird.h"


Bird::Bird()
{
}


Bird::Bird( int x, int y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;
    hitBird_flag = false;  // left of here...

    // initialize x-velocity
    mVelX = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to bird's offset
    shiftCollider();
}


void Bird::move( Gunner &gunner)
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();

    // if the bird went too far to the left 
    if( mPosX < 0 + BIRD_WIDTH ) 
    {
        delBird_flag = true;  
    }

    if( mVelX == 0 )
        mVelX = BIRD_XVEL;

}


void Bird::render( GamePlay &GP)
{
    // show the bird
	//gRBirdF2Texture.render( mPosX, mPosY );
}


void Bird::sfx_call()
{

}


void Bird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int Bird::getmCollx()
{
    return mCollider.x;
}


int Bird::getmColly()
{
    return mCollider.y;
}


int Bird::getmCollw()
{
    return mCollider.w;
}


int Bird::getmCollh()
{
    return mCollider.h;
}
