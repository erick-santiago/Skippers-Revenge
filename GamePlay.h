#ifndef GAMEPLAY_H_
#define GAMEPLAY_H_

#include <SDL2/SDL.h>
#include "LTexture.h"
#include "GTimer.h"
#include "Gunner.h"
#include <vector>
#include <memory>
#include <sstream>
#include "GameState.h"

class Bullet;


class GamePlay : public GameState
{
    friend class RBird;
    friend class BBird;
    friend class YBird;
    friend class GBird;
    friend class HBird;

    public:

        // initialize variables & load gamePlay resources
        GamePlay();

        // deallocate memory
        ~GamePlay();

        // loads media
        bool loadMedia();

        // free resources
        void close();

        // main loop functions
        void handle_events();

        void logic();

        void render();

    private:

        // timer for gamePlay            
        GTimer gameTimer;

        //The gunner that will be moving around on the screen
	    Gunner gunner;

        // initialize bullet vector
        std::vector<Bullet> bl;

        // initialize bird vector
        std::vector< std::unique_ptr<Bird> > spbv;

        //The background scrolling offset
		int scrollingOffset;

        //In memory text stream
	    std::stringstream pointsText;
        std::stringstream hpText;

        //Set text color as black
	    SDL_Color textColor;

        int birdChance;
        int optionBird;
        int birdPeriod;  // e.g., 500 is 500ms
        int verticalOffset;

        LTexture gRBirdF2Texture;
        LTexture gBBirdF3Texture;
        LTexture gYBirdF1Texture;
        LTexture gGBirdF2Texture;
        LTexture gHBirdF1Texture;

};


#endif  // GAMEPLAY_H_
