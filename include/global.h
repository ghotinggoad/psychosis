#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <stdio.h>
#include <string>

#include <SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "cTexture.h"
#include "cTimer.h"
#include "graphics.h"
#include "game.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int REFRESH_RATE;
extern const float FRAME_TIME;

extern SDL_Window* window;
extern SDL_Renderer* renderer;

#endif