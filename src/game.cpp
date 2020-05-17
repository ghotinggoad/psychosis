#include "../include/global.h"

//This is no longer SDL wrapper territory. Includes everything specific games need.


// imageTexture = texture used to load png image
cTexture imageTexture;

float angle = 0.0;
SDL_Point center = {640, 480};

void game(){

    SDL_RenderClear(renderer);
    imageTexture.renderTexture(0, 0, 1280, 960, NULL, angle, &center, SDL_FLIP_NONE);
    refreshGraphics();
}

bool loadImage(){
    return imageTexture.loadPNG("./media/background.png");
}