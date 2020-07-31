/*
 * GameOver.h
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#ifndef GAMEOVER_H_
#define GAMEOVER_H_


#include "LTexture.h"


class GameOver : public GameState
{
    public:
    
        // loads intro resources
        GameOver();

        // frees intro resources
        ~GameOver();

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


#endif  // GAMEOVER_H_
