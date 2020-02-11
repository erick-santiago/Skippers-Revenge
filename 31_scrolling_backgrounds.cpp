//Using SDL, SDL_image, standard IO, vectors, and strings
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

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;


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


//Texture wrapper class
class LTexture
{
	public:
		//Initializes variables
		LTexture();

		//Deallocates memory
		~LTexture();

		//Loads image at specified path
		bool loadFromFile( std::string path );
		
		#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
		//Creates image from font string
		bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
		#endif

		//Deallocates texture
		void free();

		//Set color modulation
		void setColor( Uint8 red, Uint8 green, Uint8 blue );

		//Set blending
		void setBlendMode( SDL_BlendMode blending );

		//Set alpha modulation
		void setAlpha( Uint8 alpha );
		
		//Renders texture at given point
		void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );

		//Gets image dimensions
		int getWidth();
		int getHeight();

	private:
		//The actual hardware texture
		SDL_Texture* mTexture;

		//Image dimensions
		int mWidth;
		int mHeight;
};

class Bird;

//The gunner that will move around on the screen
class Gunner
{
    public:
		//The dimensions of the gunner
		static const int GUNNER_WIDTH = 101;
		static const int GUNNER_HEIGHT = 65;

		//Maximum axis velocity of the gunner
		static const int GUNNER_VEL = 5;

		//Initializes the variables
		Gunner();

		//Takes key presses and adjusts the gunner's velocity
		void handleEvent( SDL_Event& e );

		//Moves the gunner
		void move( std::vector< std::unique_ptr<Bird> > &spvect );

		//Shows the gunner on the screen
		void render();

        void sfx_call();

        bool hitGunner_flag;

        int getPosX();

        int getPosY();

        bool bullet_flag; 

        bool bird_flag;

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

        void setPoints();

        Uint32 getPoints();

        void setHP();

        Uint32 getHP();

    private:
		//The X and Y offsets of the gunner
		int mPosX, mPosY;

		//The velocity of the gunner
		int mVelX, mVelY;

        // gunner's collision box
        SDL_Rect mCollider;

        // reposition coll box relative to gunner's offset
        void shiftCollider();

        // destroy points
        Uint32 points;

        // health points
        Uint32 hp;
};


class Bullet
{
    public:
        // the dimensions of the bullet
        static const int BULLET_WIDTH = 50;
        static const int BULLET_HEIGHT = 20;

        // max horizontal velocity of the bullet
        static const int BULLET_VEL = 8;

        // initializes the variables
        Bullet( int x, int y);

        // moves the bullet
        void move( std::vector< std::unique_ptr<Bird> > &spvect);

        // shows the bullet on the screen
        void render();

        bool delBullet_flag;

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

    private:
        // the X and Y offsets of the bullet
        int mPosX, mPosY;
 
        // the x velovity of the bullet
        int mVelX; 

        // bullet's collision box
        SDL_Rect mCollider;

        // reposition coll box relative to bullet's offset
        void shiftCollider();       
};


//  Abstract Bird class
class Bird
{
    public:
        // the dimensions of the bird
        const int BIRD_WIDTH = 78;
        const int BIRD_HEIGHT = 48;

        // max horizontal velocity of the bird
        const int BIRD_XVEL = 5;

        // default constructor
        Bird();

        // initializes the variables
        Bird( int x, int y);

        // moves the bird
        virtual void move() = 0;  // makes this an Abstract class

        // shows the bird on the screen
        virtual void render();

        virtual void sfx_call();

        bool delBird_flag;

        bool hitBird_flag;

        virtual int getmCollx();  // left off here... made these methods virtual.. same as move() for correct implementation

        virtual int getmColly();

        virtual int getmCollw();
 
        virtual int getmCollh();

    protected:
        // the X and Y offsets of the bird
        int mPosX, mPosY;
 
        // the x and y velocity of the bird
        int mVelX, mVelY;

        // bird's collision box
        SDL_Rect mCollider;

        // reposition coll box relative to bird's offset
        virtual void shiftCollider();
};


class RBird : public Bird
{
    public:

        // initializes the variables
        RBird( int x, int y);
    
        // max horizontal velocity of red bird
        static const int BIRD_XVEL = -8;

        void move();

        void render();

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

        void move();

        void render();

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

        void move();

        void render();

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

        void move();

        void render();

        void sfx_call();

        int getmCollx();

        int getmColly();

        int getmCollw();
 
        int getmCollh();

    private:

        // reposition coll box relative to bird's offset
        void shiftCollider();

};


class GTimer{

    public:

      // constructor
      GTimer();

      // destructor
      ~GTimer();

      // start timer
      void start();

      // capture elasped time
      float getElapsedTime();

    private:

      Uint32 mstartTicks;

      float melapsedTime;

};


//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Gunner-bird collision detector
bool checkCollisionGBx( Gunner &a, std::vector< std::unique_ptr<Bird> > &b );

//Bullet-bird collision detector
void checkCollisionBB( Bullet &a, std::vector< std::unique_ptr<Bird> > &b );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Globally used font
TTF_Font* gFont = NULL;

//Scene textures
LTexture gPointsTexture;
LTexture gHPTexture;
LTexture gHealthTexture;
LTexture gGunnerTexture;
LTexture gBGTexture;
LTexture gBulletTexture;
LTexture gRBirdF2Texture;
LTexture gBBirdF3Texture;
LTexture gYBirdF1Texture;
LTexture gGBirdF2Texture;

//The background music
Mix_Music *bgMusic = NULL;

//The sound effects used
Mix_Chunk *sfx_bullet = NULL;
Mix_Chunk *sfx_hCrow = NULL;
Mix_Chunk *sfx_lCrow = NULL;
Mix_Chunk *sfx_bPop2 = NULL;
Mix_Chunk *sfx_gHit = NULL;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile( std::string path )
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		//Color key image
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#if defined(_SDL_TTF_H) || defined(SDL_TTF_H)
bool LTexture::loadFromRenderedText( std::string textureText, SDL_Color textColor )
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );
	if( textSurface != NULL )
	{
		//Create texture from surface pixels
        mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );
		if( mTexture == NULL )
		{
			printf( "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError() );
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface( textSurface );
	}
	else
	{
		printf( "Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError() );
	}

	
	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor( Uint8 red, Uint8 green, Uint8 blue )
{
	//Modulate texture rgb
	SDL_SetTextureColorMod( mTexture, red, green, blue );
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
	//Set blending function
	SDL_SetTextureBlendMode( mTexture, blending );
}
		
void LTexture::setAlpha( Uint8 alpha )
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod( mTexture, alpha );
}

void LTexture::render( int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };

	//Set clip rendering dimensions
	if( clip != NULL )
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Gunner::Gunner()
    : bullet_flag( false ), bird_flag( false ), hitGunner_flag( false )
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 0;

    //Initialize the velocity
    mVelX = 0;
    mVelY = 0;

    // initialize collision box
    mCollider.w = GUNNER_WIDTH;
    mCollider.h = GUNNER_HEIGHT;

    // initialize points
    points = 0;
    hp = 3;

    // reposition coll box relative to gunner's offset
    shiftCollider();
}

void Gunner::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= GUNNER_VEL; break;
            case SDLK_DOWN: mVelY += GUNNER_VEL; break;
            case SDLK_LEFT: mVelX -= GUNNER_VEL; break;
            case SDLK_RIGHT: mVelX += GUNNER_VEL; break;
        }

        // shoot bullet
        switch( e.key.keysym.sym )
        {
            case SDLK_d: bullet_flag = true; break;
        }

        // create bird
        switch( e.key.keysym.sym )
        {
            case SDLK_b: bird_flag = true; break;
        }

    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += GUNNER_VEL; break;
            case SDLK_DOWN: mVelY -= GUNNER_VEL; break;
            case SDLK_LEFT: mVelX += GUNNER_VEL; break;
            case SDLK_RIGHT: mVelX -= GUNNER_VEL; break;
        }
    }
}

void Gunner::move( std::vector< std::unique_ptr<Bird> > &spvect)
{
    //Move the gunner left or right
    mPosX += mVelX;
    shiftCollider();

    // check if gunner collided with bird
    if( checkCollisionGBx( *this, spvect ) )
    {
        //delBird_flag = true;
        //Move back
        mPosX -= mVelX;
        shiftCollider();
    }

    //If the gunner went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + GUNNER_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
        shiftCollider();
    }

    //Move the gunner up or down
    mPosY += mVelY;
    shiftCollider();

    // if gunner collided with bird
    if( checkCollisionGBx( *this, spvect ) )
    {
        //delBird_flag = true;
        //Move back
        mPosY -= mVelY;
        shiftCollider();
    }

    //If the gunner went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + GUNNER_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
        shiftCollider();
    }
}

void Gunner::render()
{
    //Show the gunner
	gGunnerTexture.render( mPosX, mPosY );
}

void Gunner::sfx_call()
{
    Mix_PlayChannel( -1, sfx_gHit , 0 );
}


int Gunner::getPosX()
{
    return mPosX;
}


int Gunner::getPosY()
{
    return mPosY;
}


void Gunner::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int Gunner::getmCollx()
{
    return mCollider.x;
}


int Gunner::getmColly()
{
    return mCollider.y;
}


int Gunner::getmCollw()
{
    return mCollider.w;
}


int Gunner::getmCollh()
{
    return mCollider.h;
}

void Gunner::setPoints()
{
    points += 10;
}

void Gunner::setHP()
{
    if( hp != 0 )
        hp -= 1;
}

Uint32 Gunner::getPoints()
{
    return points;
}

Uint32 Gunner::getHP()
{
    return hp;
}


Bullet::Bullet( int x, int y)
    : delBullet_flag( false )
{
    // initialize position
    mPosX = x;
    mPosY = y;

    // initialize x-velocity
    mVelX = 0;

    // initialize collision box
    mCollider.w = BULLET_WIDTH;
    mCollider.h = BULLET_HEIGHT;

    // reposition coll box relative to gunner's offset
    shiftCollider();
}


void Bullet::move( std::vector< std::unique_ptr<Bird> > &spvect)
{
    // move the bullet along x-axis
    mPosX += mVelX;
    shiftCollider();

    // check if bullet collided with bird
    checkCollisionBB( *this, spvect );

    // if the bullet went too far to the left or right
    if( mPosX > SCREEN_WIDTH + BULLET_WIDTH * 2 )
    {
        delBullet_flag = true;  
    }

    if( mVelX == 0 )
        mVelX = BULLET_VEL;

}


void Bullet::render()
{
    // show the bullet
	gBulletTexture.render( mPosX, mPosY );
}


void Bullet::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int Bullet::getmCollx()
{
    return mCollider.x;
}


int Bullet::getmColly()
{
    return mCollider.y;
}


int Bullet::getmCollw()
{
    return mCollider.w;
}


int Bullet::getmCollh()
{
    return mCollider.h;
}


Bird::Bird()
{
}


Bird::Bird( int x, int y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;
    hitBird_flag = false;  // left of here...

    // initialize x-velocity
    mVelX = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to bird's offset
    shiftCollider();
}


void Bird::move()
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();

    // if the bird went too far to the left 
    if( mPosX < 0 + BIRD_WIDTH ) 
    {
        delBird_flag = true;  
    }

    if( mVelX == 0 )
        mVelX = BIRD_XVEL;

}


void Bird::render()
{
    // show the bird
	//gRBirdF2Texture.render( mPosX, mPosY );
}


void Bird::sfx_call()
{

}


void Bird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int Bird::getmCollx()
{
    return mCollider.x;
}


int Bird::getmColly()
{
    return mCollider.y;
}


int Bird::getmCollw()
{
    return mCollider.w;
}


int Bird::getmCollh()
{
    return mCollider.h;
}


RBird::RBird( int x, int y) 
    : Bird( x, y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;

    // initialize x-velocity
    mVelX = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to Rbird's offset
    shiftCollider();
}


void RBird::move()
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();
    //std::cout << std::endl << " " << getmCollx();

    // if the bird went too far to the left 
    if( mPosX + BIRD_WIDTH < 0 ) 
    {
        delBird_flag = true;  
    }

    if( mVelX == 0 )
        mVelX = BIRD_XVEL;

}


void RBird::render()
{
    // show the bullet
	gRBirdF2Texture.render( mPosX, mPosY );
}


void RBird::sfx_call()
{
    Mix_PlayChannel( -1, sfx_bPop2 , 0 );
    Mix_PlayChannel( -1, sfx_hCrow , 0 );
}


void RBird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int RBird::getmCollx()
{
    return mCollider.x;
}


int RBird::getmColly()
{
    return mCollider.y;
}


int RBird::getmCollw()
{
    return mCollider.w;
}


int RBird::getmCollh()
{
    return mCollider.h;
}


BBird::BBird( int x, int y) 
    : Bird( x, y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;

    // initialize x,y velocities
    mVelX = 0;
    mVelY = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to Bbird's offset
    shiftCollider();
}


void BBird::move()
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();
    //std::cout << std::endl << " " << getmCollx();

    // if the bird went too far to the left 
    if( mPosX + BIRD_WIDTH < 0 ) 
    {
        delBird_flag = true;  
    }

    // move the bird along y-axis
    mPosY += mVelY;
    shiftCollider();

    // if the bird went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + BIRD_HEIGHT > SCREEN_HEIGHT ) )
    {
        mPosY -= mVelY; // move back
        mVelY *= -1;  // negate velocity
        mPosY += mVelY;
        shiftCollider();
    }

    if( mVelX == 0 )
    {    
        mVelX = BIRD_XVEL;
        mVelY = BIRD_YVEL;
    }

}


void BBird::render()
{
    // show the bullet
	gBBirdF3Texture.render( mPosX, mPosY );
}


void BBird::sfx_call()
{
    Mix_PlayChannel( -1, sfx_bPop2 , 0 );
    Mix_PlayChannel( -1, sfx_lCrow , 0 );
}


void BBird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int BBird::getmCollx()
{
    return mCollider.x;
}


int BBird::getmColly()
{
    return mCollider.y;
}


int BBird::getmCollw()
{
    return mCollider.w;
}


int BBird::getmCollh()
{
    return mCollider.h;
}


YBird::YBird( int x, int y) 
    : Bird( x, y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;

    // initialize x,y velocities
    mVelX = 0;
    mVelY = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to Bbird's offset
    shiftCollider();
}


void YBird::move()
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();
    //std::cout << std::endl << " " << getmCollx();

    // if the bird went too far to the left 
    if( mPosX + BIRD_WIDTH < 0 ) 
    {
        delBird_flag = true;  
    }

    // move the bird along y-axis
    mPosY += mVelY;
    shiftCollider();

    // if the bird went too far up or down
    if( ( mPosY < 0 ) || ( mPosY + BIRD_HEIGHT > SCREEN_HEIGHT ) )
    {
        mPosY -= mVelY; // move back
        mVelY *= -1;  // negate velocity
        mPosY += mVelY;
        shiftCollider();
    }

    if( mVelX == 0 )
    {    
        mVelX = BIRD_XVEL;
        mVelY = BIRD_YVEL;
    }

}


void YBird::render()
{
    // show the bullet
	gYBirdF1Texture.render( mPosX, mPosY );
}


void YBird::sfx_call()
{
    Mix_PlayChannel( -1, sfx_bPop2 , 0 );
    Mix_PlayChannel( -1, sfx_lCrow , 0 );
}


void YBird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int YBird::getmCollx()
{
    return mCollider.x;
}


int YBird::getmColly()
{
    return mCollider.y;
}


int YBird::getmCollw()
{
    return mCollider.w;
}


int YBird::getmCollh()
{
    return mCollider.h;
}


GBird::GBird( int x, int y) 
    : Bird( x, y)
{
    // initialize position
    mPosX = x;
    mPosY = y;
    delBird_flag = false;

    // initialize x-velocity
    mVelX = 0;

    // initialize collision box
    mCollider.w = BIRD_WIDTH;
    mCollider.h = BIRD_HEIGHT;

    // reposition coll box relative to Rbird's offset
    shiftCollider();
}


void GBird::move()
{
    // move the bird along x-axis
    mPosX += mVelX;
    shiftCollider();
    //std::cout << std::endl << " " << getmCollx();

    // if the bird went too far to the left 
    if( mPosX + BIRD_WIDTH < 0 ) 
    {
        delBird_flag = true;  
    }

    if( mVelX == 0 )
        mVelX = BIRD_XVEL;

}


void GBird::render()
{
    // show the bullet
	gGBirdF2Texture.render( mPosX, mPosY );
}


void GBird::sfx_call()
{
    Mix_PlayChannel( -1, sfx_bPop2 , 0 );
    Mix_PlayChannel( -1, sfx_hCrow , 0 );
}

void GBird::shiftCollider()
{
	// reposition collider relative to position offsets
    mCollider.x = mPosX;
	mCollider.y = mPosY;
}


int GBird::getmCollx()
{
    return mCollider.x;
}


int GBird::getmColly()
{
    return mCollider.y;
}


int GBird::getmCollw()
{
    return mCollider.w;
}


int GBird::getmCollh()
{
    return mCollider.h;
}



GTimer::GTimer()
{
    mstartTicks = 0;
    melapsedTime = 0;
}


GTimer::~GTimer()
{
}


void GTimer::start()
{
    mstartTicks = SDL_GetTicks();
}


float GTimer::getElapsedTime()
{
    melapsedTime = SDL_GetTicks() - mstartTicks;
    return melapsedTime;
}


bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "Gunner 2.0!!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
                
                // initialize SDL Mixer and load audio file
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                { 
                    printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() ); 
                    success = false; 
                }

                //Initialize SDL_ttf
				if( TTF_Init() == -1 )
				{
					printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
					success = false;
				}

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

    //Open the font
	gFont = TTF_OpenFont( "zorque.ttf", 36 );
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
    if( !gHealthTexture.loadFromFile( "health.png" ) )
	{
		printf( "Failed to load health texture!\n" );
		success = false;
	}

    // load red bird frame2 texture
    if( !gRBirdF2Texture.loadFromFile( "RBframe2_scaled.png" ) )
	{
		printf( "Failed to load bird texture!\n" );
		success = false;
	}

    if( !gBBirdF3Texture.loadFromFile( "BBframe3_scaled.png" ) )
	{
		printf( "Failed to load bird texture!\n" );
		success = false;
	}

    if( !gYBirdF1Texture.loadFromFile( "YBframe1_scaled.png" ) )
	{
		printf( "Failed to load bird texture!\n" );
		success = false;
	}

    if( !gGBirdF2Texture.loadFromFile( "GBframe2_scaled.png" ) )
	{
		printf( "Failed to load bird texture!\n" );
		success = false;
	}

	//Load gunner texture
	if( !gGunnerTexture.loadFromFile( "Gunner_scaled.png" ) )
	{
		printf( "Failed to load gunner texture!\n" );
		success = false;
	}

    // load bullet texture
    if( !gBulletTexture.loadFromFile( "bullet1_scaled.png" ) )
	{
		printf( "Failed to load bullet texture!\n" );
		success = false;
	}

	//Load background texture
	if( !gBGTexture.loadFromFile( "BG_1024_768.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}

    // load background music
    bgMusic = Mix_LoadMUS( "air_sharks.wav" ); 
    if( bgMusic == NULL ) 
    { 
        printf( "Failed to load backgroun music... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    } 

    //Load sound effects 
    sfx_bullet = Mix_LoadWAV( "laser.wav" ); 
    if( sfx_bullet == NULL ) 
    { 
        printf( "Failed to load sfx_bullet... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }
 
    sfx_hCrow = Mix_LoadWAV( "hCrow.wav" ); 
    if( sfx_hCrow == NULL ) 
    { 
        printf( "Failed to load sfx_hCrow... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }

    sfx_lCrow = Mix_LoadWAV( "lCrow.wav" ); 
    if( sfx_lCrow == NULL ) 
    { 
        printf( "Failed to load sfx_lCrow... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }

    sfx_bPop2 = Mix_LoadWAV( "birdPop.wav" ); 
    if( sfx_bPop2 == NULL ) 
    { 
        printf( "Failed to load sfx_bPop2... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }

    sfx_gHit = Mix_LoadWAV( "gDamage.wav" ); 
    if( sfx_gHit == NULL ) 
    { 
        printf( "Failed to load sfx_gHit... SDL_mixer Error: %s\n", Mix_GetError() ); 
        success = false; 
    }

	return success;
}

void close()
{
	//Free loaded images
    gPointsTexture.free();
    gHPTexture.free();
    gHealthTexture.free();
    gRBirdF2Texture.free();
    gBBirdF3Texture.free();
    gYBirdF1Texture.free();
    gGBirdF2Texture.free();
	gGunnerTexture.free();
    gBulletTexture.free();
	gBGTexture.free();

    //Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

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

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
    TTF_Quit();
    Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}


// gunner-bird collision detector
bool checkCollisionGBx( Gunner &a, std::vector< std::unique_ptr<Bird> > &b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.getmCollx();
    rightA = a.getmCollx() + a.getmCollw();
    topA = a.getmColly();
    bottomA = a.getmColly() + a.getmCollh();

    // shift through birds
    for (auto its = b.begin(); its != b.end(); ++its) 
    {     
        //Calculate the sides of rect B
        leftB = (*its)->getmCollx();
        rightB = (*its)->getmCollx() + (*its)->getmCollw();
        topB = (*its)->getmColly();
        bottomB = (*its)->getmColly() + (*its)->getmCollh();

        if( rightA <= leftB )
        {
            //std::cout << std::endl << "test if rightA <= leftB..." << leftB;
            continue;  
        }

        if( leftA >= rightB )
        {
            //std::cout << std::endl << "test if leftA >= rightB..." << leftB;
            continue;
        }

        if( bottomA <= topB )
        {
            //std::cout << std::endl << "test if bottomA <= topB..." << topB;
            continue; 
        }

        if( topA >= bottomB )
        {
            //std::cout << std::endl << "test if topA >= bottomB..." << topB; 
            continue;
        }

        else
        {   
            //If none of the sides from A are outside B
            (*its)->delBird_flag = true;
            a.hitGunner_flag = true;
            std::cout << "destroy bird..." << std::endl; 
            return true;
        }

    }

    return false;

}


// bullet-bird collision detector
void checkCollisionBB( Bullet &a, std::vector< std::unique_ptr<Bird> > &b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.getmCollx();
    rightA = a.getmCollx() + a.getmCollw();
    topA = a.getmColly();
    bottomA = a.getmColly() + a.getmCollh();

    // shift through birds
    for (auto its = b.begin(); its != b.end(); ++its) 
    {     
        //Calculate the sides of rect B
        leftB = (*its)->getmCollx();
        rightB = (*its)->getmCollx() + (*its)->getmCollw();
        topB = (*its)->getmColly();
        bottomB = (*its)->getmColly() + (*its)->getmCollh();

        if( rightA <= leftB )
        {
            //std::cout << std::endl << "test if rightA <= leftB..." << leftB;
            continue;  
        }

        if( leftA >= rightB )
        {
            //std::cout << std::endl << "test if leftA >= rightB..." << leftB;
            continue;
        }

        if( bottomA <= topB )
        {
            //std::cout << std::endl << "test if bottomA <= topB..." << topB;
            continue; 
        }

        if( topA >= bottomB )
        {
            //std::cout << std::endl << "test if topA >= bottomB..." << topB; 
            continue;
        }

        else
        {   
            //If none of the sides from A are outside B
            (*its)->delBird_flag = true;
            (*its)->hitBird_flag = true;
            a.delBullet_flag = true;
            std::cout << std::endl << "destroy bird..."; 
            break;
        }

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
            int birdPeriod = 172;  // 500 is 500ms
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
