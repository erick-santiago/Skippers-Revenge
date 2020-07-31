/*
 * Bullet.cpp
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#include <SDL2/SDL.h>
#include <vector>
#include <memory>
#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "Bird.h"
#include "Bullet.h"


Bullet::Bullet( int x, int y)
    : delBullet_flag( false )
{
    // initialize position
    mPosX = x;
    mPosY = y;

    // initialize x-velocity
    mVelX = 0;

    // initialize collision box
    mCollider.w = BULLET_WIDTH;
    mCollider.h = BULLET_HEIGHT;

    // reposition coll box relative to gunner's offset
    shiftCollider();
}


void Bullet::move( std::vector< std::unique_ptr<Bird> > &spvect)
{
    // move the bullet along x-axis
    mPosX += mVelX;
    shiftCollider();

    // check if bullet collided with bird
    checkCollisionBB( *this, spvect );

    // if the bullet went too far to the left or right
    if( mPosX > SCREEN_WIDTH + BULLET_WIDTH * 2 )
    {
        delBullet_flag = true;  
    }

    if( mVelX == 0 )
        mVelX = BULLET_VEL;

}


void Bullet::render()
{
    // show the bullet
	gBulletTexture.render( mPosX, mPosY );
}


void Bullet::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int Bullet::getmCollx()
{
    return mCollider.x;
}


int Bullet::getmColly()
{
    return mCollider.y;
}


int Bullet::getmCollw()
{
    return mCollider.w;
}


int Bullet::getmCollh()
{
    return mCollider.h;
}




