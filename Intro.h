#ifndef INTRO_H_
#define INTRO_H_

#include "LTexture.h"


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


#endif  // INTRO_H_
