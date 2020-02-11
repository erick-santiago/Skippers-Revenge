#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include "constants.h"
#include "globals.h"
#include "functions.h"
#include "Bird.h"
#include "Bullet.h"
#include "Gunner.h"
#include "Intro.h"
#include "Title.h"
#include "GamePlay.h"
#include "GameOver.h"


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Gunner 2.0!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
                
                // initialize SDL Mixer and load audio file
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                { 
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() ); 
                    success = false; 
                }

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

			}
		}
	}

	return success;
}


bool loadMedia()
{
	//Loading success flag
	bool success = true;

    //Open the font
	gFont = TTF_OpenFont( "lazy.ttf", 36 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };
	}

	return success;
}

void close()
{
    //Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}


// gunner-bird collision detector
bool checkCollisionGBx( Gunner &a, std::vector< std::unique_ptr<Bird> > &b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.getmCollx();
    rightA = a.getmCollx() + a.getmCollw();
    topA = a.getmColly();
    bottomA = a.getmColly() + a.getmCollh();

    // shift through birds
    for (auto its = b.begin(); its != b.end(); ++its) 
    {     
        //Calculate the sides of rect B
        leftB = (*its)->getmCollx();
        rightB = (*its)->getmCollx() + (*its)->getmCollw();
        topB = (*its)->getmColly();
        bottomB = (*its)->getmColly() + (*its)->getmCollh();

        if( rightA <= leftB )
        {
            //std::cout << std::endl << "test if rightA <= leftB..." << leftB;
            continue;  
        }

        if( leftA >= rightB )
        {
            //std::cout << std::endl << "test if leftA >= rightB..." << leftB;
            continue;
        }

        if( bottomA <= topB )
        {
            //std::cout << std::endl << "test if bottomA <= topB..." << topB;
            continue; 
        }

        if( topA >= bottomB )
        {
            //std::cout << std::endl << "test if topA >= bottomB..." << topB; 
            continue;
        }

        else
        {   
            //If none of the sides from A are outside B
            (*its)->delBird_flag = true;
            a.hitGunner_flag = true;
            std::cout << "destroy bird..." << std::endl; 
            return true;
        }

    }

    return false;

}


// bullet-bird collision detector
void checkCollisionBB( Bullet &a, std::vector< std::unique_ptr<Bird> > &b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.getmCollx();
    rightA = a.getmCollx() + a.getmCollw();
    topA = a.getmColly();
    bottomA = a.getmColly() + a.getmCollh();

    // shift through birds
    for (auto its = b.begin(); its != b.end(); ++its) 
    {     
        //Calculate the sides of rect B
        leftB = (*its)->getmCollx();
        rightB = (*its)->getmCollx() + (*its)->getmCollw();
        topB = (*its)->getmColly();
        bottomB = (*its)->getmColly() + (*its)->getmCollh();

        if( rightA <= leftB )
        {
            //std::cout << std::endl << "test if rightA <= leftB..." << leftB;
            continue;  
        }

        if( leftA >= rightB )
        {
            //std::cout << std::endl << "test if leftA >= rightB..." << leftB;
            continue;
        }

        if( bottomA <= topB )
        {
            //std::cout << std::endl << "test if bottomA <= topB..." << topB;
            continue; 
        }

        if( topA >= bottomB )
        {
            //std::cout << std::endl << "test if topA >= bottomB..." << topB; 
            continue;
        }

        else
        {   
            //If none of the sides from A are outside B
            (*its)->delBird_flag = true;
            (*its)->hitBird_flag = true;
            a.delBullet_flag = true;
            std::cout << std::endl << "destroy bird..."; 
            break;
        }

    }

}


void set_next_state( int newState )
{
    //If the user doesn't want to exit
    if( nextState != STATE_EXIT )
    {
        //Set the next state
        nextState = newState;
    }
}

void change_state()
{
    //If the state needs to be changed
    if( nextState != STATE_NULL )
    {
        //Delete the current state
        if( nextState != STATE_EXIT )
        {
            delete currentState;
        }

        //Change the state
        switch( nextState )
        {
            case STATE_INTRO:
                currentState = new Intro();
                break;

            case STATE_TITLE:
                currentState = new Title();
                break;

            case STATE_GAMEPLAY:
                currentState = new GamePlay();   // left off here...
                break;

            case STATE_GAMEOVER:
                currentState = new GameOver();
                break;
   
        }

        //Change the current state ID
        stateID = nextState;

        //NULL the next state ID
        nextState = STATE_NULL;
    }
}





