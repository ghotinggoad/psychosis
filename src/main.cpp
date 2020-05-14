#include "../include/global.h"
#include <iostream>


const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool run;

using namespace std;

// main() will not compile with mingw32 and SDL, "https://wiki.libsdl.org/FAQWindows#I_get_.22Undefined_reference_to_.27SDL_main.27.22_..." >> miscellaneous
int main(int argc, char *argv[]){
    run = init(SCREEN_WIDTH, SCREEN_HEIGHT);
    
    SDL_Event event;
    
    while(run){
        while(SDL_PollEvent(&event) != 0){
            if(event.type == SDL_QUIT) run = false;
        }
        refreshWindow();
    }
    quit();
    return 0;
}