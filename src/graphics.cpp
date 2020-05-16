#include "../include/global.h"

// Window we're rendering to 
SDL_Window* window = NULL;
// Surfaces are rendered by the CPU (meaning software rendered), "contains pixels of an image along with all data needed to render it"
// The following renderer is the rendered surface shown in the mainwindow
SDL_Renderer* renderer = NULL;

// fpsTexture = texture used to store rendered text, fpsFont = storing umeboshi_.ttf font file for FPS
cTexture fpsTexture;
TTF_Font* fpsFont;

// timer used to measure time between frames, used for delay to attain inaccurate FPS lock
cTimer frameLimitTimer;
// timer and count used to measure FPS
cTimer frameCountTimer;
int frameCount = 0;

// initialize SDL2 windows and graphics handler, also PNG and TTF dependencies
bool initGraphics(int SCREEN_WIDTH,int SCREEN_HEIGHT){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        // create window
        window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL ){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        // IMG_Init will return the value that was parsed to it if successful
        if(!(IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG){
            printf("SDL_image libraries cannot be initialized! SDL_image Error: %s\n", IMG_GetError());
            success = false;
        }
        else{
            // create a renderer that is hardware accelerated
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        }
        if(TTF_Init() == -1){
            printf("SDL_ttf libraries cannot be initialized! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
    }
    success = initFPSCounter();
    return success;
}

bool initFPSCounter(){
    frameCountTimer.start();
    frameLimitTimer.start();

    // load TTF to font, the int behind refers to DPI
    fpsFont = TTF_OpenFont("./media/umeboshi_.ttf", SCREEN_WIDTH/24);
    if(fpsFont == NULL) printf("/media/umeboshi_.ttf cannot be loaded!");
    // sets text color of loaded font texture to 
    fpsTexture.setTextColor(0, 0, 0, 255);
    // Change font style, includes TTF_STYLE_NORMAL, TTF_STYLE_BOLD, TTF_STYLE_ITALIC, TTF_STYLE_UNDERLINE, TTF_STYLE_STRIKETHROUGH
    TTF_SetFontStyle(fpsFont, TTF_STYLE_BOLD);
    return fpsFont != NULL;
}

void frameCounter(){
    // framesCount is added every render cycle, divided by 1000ms to get FPS
    int avgFPS = frameCount/(frameCountTimer.getTicks()/1000.f);
    fpsTexture.renderText(0, 0, std::to_string(avgFPS).append("FPS"), fpsFont, 0.0, NULL, SDL_FLIP_NONE);
    // this resets the FPS counter every 2.5 seconds, to retain accuracy after program has been running for a long time
    if(frameCount > REFRESH_RATE*2.5){
        frameCountTimer.start();
        frameCount = 0;
    }
    frameCount++;
}

// non-vsync method
void frameLimiter(){
    int frameRemainingTicks = frameLimitTimer.getTicks();
    if(frameRemainingTicks < FRAME_TIME) SDL_Delay(FRAME_TIME - frameRemainingTicks);
    // restarted frameLimitTimer so that frameRemainingTicks will ideally be between 0 and FRAME_TIME every single loop
    frameLimitTimer.start();
}

// this is used to render all graphics wrapper function before game specific renders onto it.
void refreshGraphics(){
    frameCounter();
    frameLimiter();
    // SDL_Delay(16);
    SDL_RenderPresent(renderer);
}

void exitGraphics(){
    // Free loaded texture
    fpsTexture.destroyTexture();
    // Free fonts
    TTF_CloseFont(fpsFont);
    fpsFont = NULL;

    // Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    window = NULL;
    renderer = NULL;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}