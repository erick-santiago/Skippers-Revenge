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
#include "Title.h"
#include "GamePlay.h"



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
			//Set the current state ID
            stateID = STATE_INTRO;

            //Set the current game state object
            currentState = new Intro();

			//While application is running
			while( stateID != STATE_EXIT )
			{
				//Do state event handling
                currentState->handle_events();

                //Do state logic
                currentState->logic();

                //Change state if needed
                change_state();

                //Do state rendering
                currentState->render();

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
