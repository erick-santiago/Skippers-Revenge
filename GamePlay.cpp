/*
 * GamePlay.cpp
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
#include "GameState.h"
#include "Intro.h"
#include "GamePlay.h"


GamePlay::GamePlay()
{
    scrollingOffset = 0;

    textColor = { 47, 79, 79, 255 };

    birdPeriod = 165;  // e.g., 500 is 500ms

    // load media
    if( !loadMedia() )
		printf( "Failed to load media!\n" );

}

bool GamePlay::loadMedia()
{
	//Loading success flag
	bool success = true;

    //Open the font
	gFont = TTF_OpenFont( "Media/zorque.ttf", 36 );
	if( gFont == NULL )
	{
		printf( "Failed to load ARCADE font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };
	}

    // load health texture
    if( !gHealthTexture.loadFromFile( "Media/health.png" ) )
	{
		printf( "Failed to load health texture!\n" );
		success = false;
	}

    // load red bird frame2 texture
    if( !gRBirdF2Texture.loadFromFile( "Media/RBframe2_scaled.png" ) )
	{
		printf( "Failed to load bird texture!\n" );
		success = false;
	}

    if( !gBBirdF3Texture.loadFromFile( "Media/BBframe3_scaled.png" ) )
	{
		printf( "Failed to load bird texture!\n" );
		success = false;
	}

    if( !gYBirdF1Texture.loadFromFile( "Media/YBframe1_scaled.png" ) )
	{
		printf( "Failed to load bird texture!\n" );
		success = false;
	}

    if( !gGBirdF2Texture.loadFromFile( "Media/GBframe2_scaled.png" ) )
	{
		printf( "Failed to load bird texture!\n" );
		success = false;
	}

    if( !gHBirdF1Texture.loadFromFile( "Media/HBframe1_scaled.png" ) )
	{
		printf( "Failed to load bird texture!\n" );
		success = false;
	}

	//Load gunner texture
	if( !gGunnerTexture.loadFromFile( "Media/Gunner_scaled.png" ) )
	{
		printf( "Failed to load gunner texture!\n" );
		success = false;
	}

    // load bullet texture
    if( !gBulletTexture.loadFromFile( "Media/bullet1_scaled.png" ) )
	{
		printf( "Failed to load bullet texture!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadFromFile( "Media/BG_1024_768.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

    // load background music
    bgMusic = Mix_LoadMUS( "Media/air_sharks.wav" ); 
    if( bgMusic == NULL ) 
    { 
        printf( "Failed to load backgroun music... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    } 

    //Load sound effects 
    sfx_bullet = Mix_LoadWAV( "Media/laser.wav" ); 
    if( sfx_bullet == NULL ) 
    { 
        printf( "Failed to load sfx_bullet... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }
 
    sfx_hCrow = Mix_LoadWAV( "Media/hCrow.wav" ); 
    if( sfx_hCrow == NULL ) 
    { 
        printf( "Failed to load sfx_hCrow... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }

    sfx_lCrow = Mix_LoadWAV( "Media/lCrow.wav" ); 
    if( sfx_lCrow == NULL ) 
    { 
        printf( "Failed to load sfx_lCrow... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }

    sfx_bPop2 = Mix_LoadWAV( "Media/birdPop.wav" ); 
    if( sfx_bPop2 == NULL ) 
    { 
        printf( "Failed to load sfx_bPop2... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }

    sfx_gHit = Mix_LoadWAV( "Media/gDamage.wav" ); 
    if( sfx_gHit == NULL ) 
    { 
        printf( "Failed to load sfx_gHit... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }

    // start background music
    Mix_PlayMusic( bgMusic, -1);

    // timer for gamePlay    
    gameTimer.start();

    // initialize random seed:
    srand( time(NULL) );

	return success;
}

void GamePlay::close()
{
	//Free loaded images
    gPointsTexture.free();
    gHPTexture.free();
    gHealthTexture.free();
    gRBirdF2Texture.free();
    gBBirdF3Texture.free();  // left off here... is this the right spot to free these resources?
    gYBirdF1Texture.free();
    gGBirdF2Texture.free();
    gHBirdF1Texture.free();
	gGunnerTexture.free();
    gBulletTexture.free();
	gBGTexture.free();

    //Free the sound effects 
    Mix_FreeChunk( sfx_bullet );  
    sfx_bullet = NULL; 
    Mix_FreeChunk( sfx_hCrow );
    sfx_hCrow = NULL;
    Mix_FreeChunk( sfx_lCrow );
    sfx_lCrow = NULL;
    Mix_FreeChunk( sfx_bPop2 );
    sfx_bPop2 = NULL;
    Mix_FreeChunk( sfx_gHit );
    sfx_gHit = NULL;

    //Free the music 
    Mix_FreeMusic( bgMusic ); 
    bgMusic = NULL;

}

GamePlay::~GamePlay()
{
    // free resources
    close();

}

void GamePlay::handle_events()
{
    //Handle events in queue
    while( SDL_PollEvent( &e ) != 0 )
	{
	    //User requests quit
        if( e.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }

        else if( gunner.dedGunner_flag == true )
        {
            //Transition to GameOver
            set_next_state( STATE_GAMEOVER );
            gunner.dedGunner_flag = false;
        }

		//Handle input for the gunner
		gunner.handleEvent( e );
	}

}

void GamePlay::logic()
{
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
        optionBird = rand() % 5 + 1;

        if( optionBird == 1)
        {        
            verticalOffset = rand() % 550;  // 728                 

            spbv.push_back( std::make_unique<RBird>(SCREEN_WIDTH , verticalOffset ) );
            gunner.bird_flag = false;  
            std::cout << "optionBird1 created..." << std::endl;
        }

        if( optionBird == 2)
        {
            verticalOffset = rand() % 550;  // 710

            spbv.push_back( std::make_unique<BBird>(SCREEN_WIDTH , verticalOffset ) );
            gunner.bird_flag = false;
            std::cout << "optionBird2 created..." << verticalOffset << std::endl;
        }

        if( optionBird == 3)
        {
            verticalOffset = rand() % 550;  // 710

            spbv.push_back( std::make_unique<YBird>(SCREEN_WIDTH , verticalOffset ) );
            gunner.bird_flag = false;
            std::cout << "optionBird3 created..." << verticalOffset << std::endl;
        }

        if( optionBird == 4)
        {
            verticalOffset = rand() % 550;  // 723                

            spbv.push_back( std::make_unique<GBird>(SCREEN_WIDTH , verticalOffset ) );
            gunner.bird_flag = false;  
            std::cout << "optionBird4 created..." << std::endl;
        }

        if( optionBird == 5)
        {
            verticalOffset = rand() % 540;  // 710

            spbv.push_back( std::make_unique<HBird>(SCREEN_WIDTH , verticalOffset ) );
            gunner.bird_flag = false;
            std::cout << "optionBird5 created..." << verticalOffset << std::endl;
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
        (*its)->move( gunner);
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

}

void GamePlay::render()
{
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
        (*its)->render( *this);
                
    // render bullets
    for (auto it = bl.begin(); it != bl.end(); ++it) 
        it->render();

    // render Gunner
	gunner.render();

}
