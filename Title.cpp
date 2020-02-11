#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "constants.h"
#include "LTexture.h"
#include "globals.h"
#include "functions.h"
#include "GameState.h"
#include "Title.h"


Title::Title()
{
    // load media
    if( !loadMedia() )
		printf( "Failed to load media!\n" );
	
}

Title::~Title()
{
    // free resources
    close();
}

bool Title::loadMedia()
{
    //Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont( "lazy.ttf", 52 );  // left off here...
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

    // load background music
    bgMusic = Mix_LoadMUS( "titleMusic.wav" ); 
    if( bgMusic == NULL ) 
    { 
        printf( "Failed to load backgroun music... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    } 

	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };
		
		//Load stop prompt texture
		if( !gMessage.loadFromRenderedText( "SKIPPER'S REVENGE!", textColor ) )
		{
			printf( "Unable to render start/stop prompt texture!\n" );
			success = false;
		}
		
	}

    // start background music
    Mix_PlayMusic( bgMusic, -1);

	return success;
}

void Title::close()
{
    // free loaded images
    gBGTexture.free();
    gMessage.free();
}

void Title::handle_events()
{
    //While there's events to handle
    while( SDL_PollEvent( &e) )
    {
        //User requests quit
        if( e.type == SDL_QUIT )
        {
            //Quit the program
            set_next_state( STATE_EXIT );
        }
        //If the user pressed enter
        else if( ( e.type == SDL_KEYDOWN && e.key.repeat == 0 ) && ( e.key.keysym.sym == SDLK_RETURN ) )
        {
            //Move to the title screen
            set_next_state( STATE_GAMEPLAY );
        }
    }
}

void Title::logic()
{

}

void Title::render()
{
    // render background
    gBGTexture.render( 0, 0);

    // render message
    gMessage.render( ( SCREEN_WIDTH - gMessage.getWidth() ) / 2, ( SCREEN_HEIGHT - gMessage.getHeight() ) / 2);
}
