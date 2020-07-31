/*
 * Title.h
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#ifndef TITLE_H_
#define TITLE_H_


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


#endif  // TITLE_H_
