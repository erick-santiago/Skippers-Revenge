#ifndef GLOBALS_H_
#define GLOBALS_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include "LTexture.h"
#include "GameState.h"

//The window we'll be rendering to
extern SDL_Window *gWindow;

//The window renderer
extern SDL_Renderer *gRenderer;

//Globally used font
extern TTF_Font *gFont;

// Event handler
extern SDL_Event e;


//Scene textures
extern LTexture gPointsTexture;
extern LTexture gHPTexture;
extern LTexture gHealthTexture;
extern LTexture gGunnerTexture;
extern LTexture gBGTexture;
extern LTexture gBulletTexture;
extern LTexture gRBirdF2Texture;
extern LTexture gBBirdF3Texture;
extern LTexture gYBirdF1Texture;
extern LTexture gGBirdF2Texture;

//The background music
extern Mix_Music *bgMusic;

//The sound effects used
extern Mix_Chunk *sfx_bullet;
extern Mix_Chunk *sfx_hCrow;
extern Mix_Chunk *sfx_lCrow;
extern Mix_Chunk *sfx_bPop2;
extern Mix_Chunk *sfx_gHit;

// state variables
extern int stateID;
extern int nextState;

extern GameState *currentState;

#endif  // GLOBALS_H_
