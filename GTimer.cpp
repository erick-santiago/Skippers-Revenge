/*
 * GTimer.cpp
 *
 *  Created on: May, 2019
 *      Author: esantiago
 */

#include <SDL2/SDL.h>
#include "GTimer.h"


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
