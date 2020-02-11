#ifndef GAMESTATE_H_
#define GAMESTATE_H_


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

#endif // GAMESTATE_H_
