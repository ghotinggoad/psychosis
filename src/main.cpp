#include "../include/global.h"
#include <iostream>

// designed resolution = resolution game sprites are designed for e.g. resolution of background file that is supposed to fill the screen
// sprite has designed resolution e.g. 960p , ratio scaling applied with "texture/(designed resolution/target resolution)" e.g. 960/480 = 2

// designed resolution has been set to 1280*960p for development

const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 960;
const int REFRESH_RATE = 60;
const float FRAME_TIME = 1000/60.f;

bool run;

SDL_Event event;

// main() will not compile with mingw32 and SDL, "https://wiki.libsdl.org/FAQWindows#I_get_.22Undefined_reference_to_.27SDL_main.27.22_..." >> miscellaneous
int main(int argc, char *argv[]){
    (void)(argc);
    (void)(argv);

    run = initGraphics(SCREEN_WIDTH, SCREEN_HEIGHT);
    run = loadImage();
    
    while(run){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT) run = false;
        }
        game();
    }
    exitGraphics();
    return 0;
}