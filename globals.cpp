#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "LTexture.h"
#include "GameState.h"
#include "globals.h"


//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The window renderer
SDL_Renderer *gRenderer = NULL;

//Globally used font
TTF_Font *gFont = NULL;

//Event handler
SDL_Event e;


//Scene textures
LTexture gPointsTexture;
LTexture gHPTexture;
LTexture gHealthTexture;
LTexture gGunnerTexture;
LTexture gBGTexture;
LTexture gBulletTexture;
//LTexture gRBirdF2Texture;  // left off here... removed these textures from global scope
//LTexture gBBirdF3Texture;
//LTexture gYBirdF1Texture;
//LTexture gGBirdF2Texture;

//The background music
Mix_Music *bgMusic = NULL;

//The sound effects used
Mix_Chunk *sfx_bullet = NULL;
Mix_Chunk *sfx_hCrow = NULL;
Mix_Chunk *sfx_lCrow = NULL;
Mix_Chunk *sfx_bPop2 = NULL;
Mix_Chunk *sfx_gHit = NULL;

// state variables
int stateID = STATE_NULL;
int nextState = STATE_NULL;

GameState *currentState = NULL;

