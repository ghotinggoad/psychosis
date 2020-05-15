#include "../include/global.h"

//This is no longer SDL wrapper territory. Includes everything specific games need.


// imageTexture = texture used to load png image
cTexture imageTexture;

void game(){
    SDL_RenderClear(renderer);
    imageTexture.renderTexture(0, 0, 1280, 960, NULL);
    refreshGraphics();
}

void loadImage(){
    imageTexture.loadPNG("./media/background.png");
}
/*
// rewrite this to load individual file types inbetween loading stage
bool loadMedia(){
    bool success = true;
    // load PNG to cTexture class type imageTexture
    if(!imageTexture.loadPNG("./media/background.png", imageRenderer)){
        printf("/media/test.png cannot be loaded!");
        success = false;
    }
    return success;
}

void background(){
    // renders the image onto renderer called imageRenderer
    imageTexture.renderTexture(0, 0, NULL, imageRenderer);
}


void refreshWindow(){
    SDL_RenderClear(imageRenderer);
    // renders the text (the FPS counter in this case)
    // fpsTexture.renderText(0, 0, std::to_string(getFPS()), imageRenderer, fpsFont);
    fpsTexture.renderText(0, 0, "なんでやねん！", imageRenderer, fpsFont);
    // renders the text in imageRenderer at x = 0, y = 0, NULL means it's not a clipped quad
    fpsTexture.renderTexture(0, 0, NULL, imageRenderer);
    // refresh renderer to show the latest image in the window
    SDL_RenderPresent(imageRenderer);

    // frameRemainingTicks is used so that it doesn't change during runtime, used to delay the program for n seconds until next frame at 60hz
    int frameRemainingTicks = framesCapTimer.getTicks();
    if(frameRemainingTicks < FRAME_TIME) SDL_Delay(FRAME_TIME - frameRemainingTicks);
    framesCapTimer.start();
}
*/