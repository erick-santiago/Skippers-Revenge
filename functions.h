/*
 * functions.h
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#ifndef FUNCTIONS_H_    
#define FUNCTIONS_H_

#include <vector>
#include <memory>

class Bird;
class Bullet;
class Gunner;


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Gunner-bird collision detector
bool checkCollisionGBx( Gunner &a, std::vector< std::unique_ptr<Bird> > &b );

//Bullet-bird collision detector
void checkCollisionBB( Bullet &a, std::vector< std::unique_ptr<Bird> > &b );

// State status manager
void set_next_state(int newState);

// state changer
void change_state();


#endif  // FUNCTIONS_H_


