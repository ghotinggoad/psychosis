#include "../include/global.h"

// Window we're rendering to 
SDL_Window* window = NULL;
// Surfaces are rendered by the CPU (meaning software rendered), "contains pixels of an image along with all data needed to render it"
// The following renderer is the rendered surface shown in the mainwindow
SDL_Renderer* imageRenderer = NULL;

// imageTexture = texture used to load png image
cTexture imageTexture;

// textTexture = texture used to store rendered text, textColor = 8bit RGB values, umeboshiFont = storing umeboshi_.ttf font file
cTexture textTexture;
SDL_Color textColor = {0, 0, 0};
TTF_Font* umeboshiFont;

// timer used to measure time between frames, used for delay to attain FPS lock (inaccurate)
cTimer framesCapTimer;

// timer used to measure FPS
cTimer framesCountTimer;
int framesCount = 0;

// initialize SDL2 windows and graphics handler, also PNG and TTF dependencies
bool init(int SCREEN_WIDTH,int SCREEN_HEIGHT){
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
                imageRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        }
        if(TTF_Init() == -1){
            printf("SDL_ttf libraries cannot be initialized! SDL_ttf Error: %s\n", TTF_GetError());
            success = false;
        }
    }
    success = loadMedia();
    framesCountTimer.start();
    framesCapTimer.start();
    return success;
}

bool loadMedia(){
    bool success = true;
    // load PNG to cTexture class type imageTexture
    if(!imageTexture.loadFromFile("./media/background.png", imageRenderer)){
        printf("/media/test.png cannot be loaded!");
        success = false;
    }
    umeboshiFont = TTF_OpenFont("./media/umeboshi_.ttf", 28);
    if(umeboshiFont == NULL){
        printf("/media/umeboshi_.ttf cannot be loaded!");
        success = false;
    }
    else{
        if(!textTexture.loadFromRenderedText("KEK", textColor, imageRenderer)){
            printf("Failed to render text texture!\n");
            success = false;
        }
    }
    return success;
}

void refreshWindow(){
    SDL_RenderClear(imageRenderer);
    // renders the image onto renderer called imageRenderer
    imageTexture.renderTexture(imageRenderer);
    // renders the text (the FPS counter in this case)
    textTexture.loadFromRenderedText(std::to_string(getFPS()), textColor, imageRenderer);
    // renders the text in imageRenderer at x = 0, y = 0, NULL means it's not a clipped quad, size is ???
    textTexture.renderSprite(0, 0, NULL, imageRenderer);
    // refresh renderer to show the latest image in the window
    SDL_RenderPresent(imageRenderer);

    // frameRemainingTicks is used so that it doesn't change during runtime, used to delay the program for n seconds until next frame at 60hz
    int frameRemainingTicks = framesCapTimer.getTicks();
    if(frameRemainingTicks < 1000/60.f) SDL_Delay(1000/60.f - frameRemainingTicks);
    framesCapTimer.start();
}

float getFPS(){
    // this resets the FPS counter every 2.5 seconds, to retain accuracy after program has been running for a long time
    if(framesCount >= 150){
        // restart timer to get 0 ticks again
        framesCountTimer.start();
        framesCount = 0;
    }
    // framesCount is added every render cycle, divided by 1000ms to get FPS
    float avgFPS = framesCount/(framesCountTimer.getTicks()/1000.f);
    framesCount++;
    return avgFPS;
}

void quit(){
    // Free loaded images
    imageTexture.clearTexture();
    textTexture.clearTexture();
    // Free fonts
    TTF_CloseFont(umeboshiFont);
    umeboshiFont = NULL;

    // Destroy window
    SDL_DestroyRenderer(imageRenderer);
    SDL_DestroyWindow(window);
    window = NULL;
    imageRenderer = NULL;

    // Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}