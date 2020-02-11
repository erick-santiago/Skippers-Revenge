#ifndef BIRDS_H_
#define BIRDS_H_

class GamePlay;
class Gunner;


class RBird : public Bird
{
    public:

        // initializes the variables
        RBird( int x, int y);
    
        // max horizontal velocity of red bird
        static const int BIRD_XVEL = -8;

        void move( Gunner &gunner);

        void render( GamePlay &GP);

        void sfx_call();

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

    private:

        // reposition coll box relative to bird's offset
        void shiftCollider();

};


class BBird : public Bird
{
    public:

        // the dimensions of the bird
        const int BIRD_WIDTH = 75;
        const int BIRD_HEIGHT = 54;

        // initializes the variables
        BBird( int x, int y);
    
        // max horizontal velocity of blue bird
        const int BIRD_XVEL = -4;

        //  max vertical velocity of blue bird        
        const int BIRD_YVEL = -6;        

        void move( Gunner &gunner);

        void render( GamePlay &GP);

        void sfx_call();

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

    private:

        // reposition coll box relative to bird's offset
        void shiftCollider();

};


class YBird : public Bird
{
    public:

        // the dimensions of the bird
        const int BIRD_WIDTH = 78;
        const int BIRD_HEIGHT = 50;

        // initializes the variables
        YBird( int x, int y);
    
        // max horizontal velocity ofbird
        const int BIRD_XVEL = -4;

        //  max vertical velocity of bird        
        const int BIRD_YVEL = 5;        

        void move( Gunner &gunner);

        void render( GamePlay &GP);

        void sfx_call();

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

    private:

        // reposition coll box relative to bird's offset
        void shiftCollider();

};


class GBird : public Bird
{
    public:

        // the dimensions of the bird
        const int BIRD_WIDTH = 78;
        const int BIRD_HEIGHT = 49;

        // initializes the variables
        GBird( int x, int y);
    
        // max horizontal velocity of bird
        static const int BIRD_XVEL = -8;

        void move( Gunner &gunner);

        void render( GamePlay &GP);

        void sfx_call();

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

    private:

        // reposition coll box relative to bird's offset
        void shiftCollider();

};


class HBird : public Bird
{
    public:

        // the dimensions of the bird
        const int BIRD_WIDTH = 72;
        const int BIRD_HEIGHT = 58;

        // initializes the variables
        HBird( int x, int y);
    
        // max horizontal velocity of bird
        const int BIRD_XVEL = -6;

        //  max vertical velocity of bird        
        const int BIRD_YVEL = 2;        

        void move( Gunner &gunner);

        void render( GamePlay &GP);

        void sfx_call();

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

    private:

        // reposition coll box relative to bird's offset
        void shiftCollider();

};


#endif BIRDS_H_
