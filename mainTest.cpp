/*
 * main.cpp
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <sstream>
#include "constants.h"
#include "LTexture.h"
#include "globals.h"
#include "functions.h"
#include "Bird.h"
#include "Birds.h"
#include "Bullet.h"
#include "Gunner.h"
#include "GTimer.h"


// Game States
enum GameStates
{
    STATE_NULL,
    STATE_INTRO,
    STATE_TITLE,
    STATE_CONTROLS,
    STATE_HIGHSCORES,
    STATE_GAMEPLAY,
    STATE_GAMEOVER,
    STATE_EXIT,
};


// Game State base class (abstract)
class GameState
{
    public:
        
        virtual void handle_events() = 0;

        virtual void logic() = 0;
    
        virtual void render() = 0;

        virtual ~GameState(){};

};


// State status manager
void set_next_state(int newState);

// state changer
void change_state();


// state variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;

GameState *currentState = NULL;


class Intro : public GameState
{
    public:
    
        // loads intro resources
        Intro();

        // frees intro resources
        ~Intro();

        // loads media
        bool loadMedia();

        // free resources
        void close();

        // main loop functions
        void handle_events();

        void logic();

        void render();

    private:

        // intro background
        LTexture gBGTexture;

        // intro message
        LTexture gMessage;

};


class Title : public GameState
{
    public:

        // loads Title resources
        Title();

        // frees Title resources
        ~Title();

        // loads media
        bool loadMedia();

        // free resources
        void close();

        // main loop functions
        void handle_events();

        void logic();

        void render();

    private:

        // Title screen background
        LTexture gBGTexture;

        // intro screen message
        LTexture gMessage;

};

Intro::Intro()
{
    // load media
    if( !loadMedia() )
		printf( "Failed to load media!\n" );
	
}

Intro::~Intro()
{
    // free resources
    close();
}

bool Intro::loadMedia()
{
    //Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "lazy.ttf", 32 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

    if( !gBGTexture.loadFromFile( "lazyBG.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };
		
		//Load stop prompt texture
		if( !gMessage.loadFromRenderedText( "Wild Chicken Production Presents...", textColor ) )
		{
			printf( "Unable to render start/stop prompt texture!\n" );
			success = false;
		}
		
	}

	return success;
}

void Intro::close()
{
    // free loaded images
    gBGTexture.free();
    gMessage.free();
}

void Intro::handle_events()
{
    //While there's events to handle
    while( SDL_PollEvent( &e) )
    {
        //If the user has Xed out the window
        if( e.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        //If the user pressed enter
        else if( ( e.type == SDL_KEYDOWN ) && ( e.key.keysym.sym == SDLK_RETURN ) )
        {
            //Move to the title screen
            set_next_state( STATE_GAMEPLAY );
        }
    }
}

void Intro::logic()
{

}

void Intro::render()
{
    // render background
    gBGTexture.render( 0, 0);

    // render message
    gMessage.render( ( SCREEN_WIDTH - gMessage.getWidth() ) / 2, ( SCREEN_HEIGHT - gMessage.getHeight() ) / 2);
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




int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

            // start background music
            Mix_PlayMusic( bgMusic, -1);

            // timer for game            
            GTimer gameTimer;
            gameTimer.start();

            // initialize random seed:
            srand( time(NULL) );

            int birdChance;
            int optionBird;
            int birdPeriod = 172;  // e.g., 500 is 500ms
            int verticalOffset;

			//The gunner that will be moving around on the screen
			Gunner gunner;

            // initialize bullet vector
            std::vector<Bullet> bl;

            // initialize bird vector
            std::vector< std::unique_ptr<Bird> > spbv;

			//The background scrolling offset
			int scrollingOffset = 0;

            //In memory text stream
			std::stringstream pointsText;
            std::stringstream hpText;

            //Set text color as black
			SDL_Color textColor = { 47, 79, 79, 255 };

			//While application is running
			while( !quit )
			{
				//Handle events in queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}

					//Handle input for the gunner
					gunner.handleEvent( e );
				}

                if( gameTimer.getElapsedTime() > birdPeriod ) 
                {
                    birdChance = rand() % 2;
                    std::cout << birdChance << std::endl;

                    if( birdChance == 1)
                    {    
                        std::cout << std::endl << gameTimer.getElapsedTime() << std::endl;
                        gunner.bird_flag = true;
                        gameTimer.start();
                    }
                    
                    else
                        gameTimer.start();
                }
                    

                // if bullet flag is set, create new bullet
                if( gunner.bullet_flag )
                {
                    Mix_PlayChannel( -1, sfx_bullet, 0 );            
        
                    Bullet bullet( gunner.getPosX() + 75 , gunner.getPosY() + 35 );
                    bl.push_back( bullet );
                    gunner.bullet_flag = false;
                }

                // if bird flag is set, create new bird
                if( gunner.bird_flag )
                {
                    optionBird = rand() % 4 + 1;

                    if( optionBird == 1)
                    {        
                        verticalOffset = rand() % 728;                   

                        spbv.push_back( std::make_unique<RBird>(SCREEN_WIDTH , verticalOffset ) );
                        gunner.bird_flag = false;  
                        std::cout << "optionBird1 created..." << std::endl;
                    }

                    if( optionBird == 2)
                    {
                        verticalOffset = rand() % 710;

                        spbv.push_back( std::make_unique<BBird>(SCREEN_WIDTH , verticalOffset ) );
                        gunner.bird_flag = false;
                        std::cout << "optionBird2 created..." << verticalOffset << std::endl;
                    }

                    if( optionBird == 3)
                    {
                        verticalOffset = rand() % 710;

                        spbv.push_back( std::make_unique<YBird>(SCREEN_WIDTH , verticalOffset ) );
                        gunner.bird_flag = false;
                        std::cout << "optionBird3 created..." << verticalOffset << std::endl;
                    }

                    if( optionBird == 4)
                    {
                        verticalOffset = rand() % 723;                   

                        spbv.push_back( std::make_unique<GBird>(SCREEN_WIDTH , verticalOffset ) );
                        gunner.bird_flag = false;  
                        std::cout << "optionBird4 created..." << std::endl;
                    }
                }

				//Move the gunner
				gunner.move( spbv );  // left off here need to implement collision detection with birds

                // move the bullets
                std::vector<Bullet>::iterator it;
                for (auto it = bl.begin(); it != bl.end(); ++it) 
                { 
                    it->move( spbv );

                    if( it->delBullet_flag == true )
                    {
                        bl.erase( it-- );
                        std::cout << std::endl << "bullet destroyed...";
                    }

                }

                // move the birds
                for (auto its = spbv.begin(); its != spbv.end(); ++its) 
                { 
                    (*its)->move();
                    //std::cout << std::endl << " " << (*its)->getmCollx();

                    if( (*its)->hitBird_flag == true )
                    {
                        (*its)->sfx_call();
                        (*its)->hitBird_flag = false;
                        gunner.setPoints();
                    }    

                    if( (*its)->delBird_flag == true )
                    {        
                        if( gunner.hitGunner_flag == true )
                        {
                            gunner.sfx_call();
                            gunner.setHP();
                            gunner.hitGunner_flag = false;
                        }

                        std::cout << std::endl << "bird destroyed..." << std::endl; 
                        spbv.erase( its-- );
                    }
                }

				//Scroll background
				--scrollingOffset;
				if( scrollingOffset < -gBGTexture.getWidth() )
				{
					scrollingOffset = 0;
				}

                //Set text to be rendered
				pointsText.str( "" );
				pointsText << "Score: " << gunner.getPoints();  // << ( timer.getTicks()

                hpText.str( "" );
                hpText << gunner.getHP();

				//Render points text
				if( !gPointsTexture.loadFromRenderedText( pointsText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}

                //Render HP text
				if( !gHPTexture.loadFromRenderedText( hpText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background
				gBGTexture.render( scrollingOffset, 0 );
				gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

                // render healthTexture
                gHealthTexture.render( 2 , ( SCREEN_HEIGHT - gHealthTexture.getHeight() ) ); 

                // render HP
                gHPTexture.render( 100 , (SCREEN_HEIGHT - gHPTexture.getHeight()) - 18 );

                // render text
                gPointsTexture.render( ( SCREEN_WIDTH - gPointsTexture.getWidth() ) / 2, 2 );  //( SCREEN_HEIGHT - gTimeTextTexture.getHeight() ) / 3

                // render birds
                for (auto its = spbv.begin(); its != spbv.end(); ++its) 
                    (*its)->render();
                
                // render bullets
                for (it = bl.begin(); it != bl.end(); ++it) 
                    it->render();

                // render Gunner
				gunner.render();

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
