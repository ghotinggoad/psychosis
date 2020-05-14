#include "../include/global.h"

// Window we're rendering to 
SDL_Window* window = NULL;
// Surfaces are rendered by the CPU (meaning software rendered), "contains pixels of an image along with all data needed to render it"
// The following renderer is the rendered surface shown in the mainwindow
SDL_Renderer* imageRenderer = NULL;

cTexture imageTexture;
cTexture textTexture;
TTF_Font* umeboshiFont;

cTimer framesCountTimer;
cTimer framesCapTimer;

int framesCount = 0;
SDL_Color textColor = {0, 0, 0};

bool init(int SCREEN_WIDTH,int SCREEN_HEIGHT){
    bool success = true;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    else{
        //Create window
        window = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if(window == NULL ){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        }
        if(!(IMG_Init(IMG_INIT_PNG)) & IMG_INIT_PNG){
            printf("SDL_image libraries cannot be initialized! SDL_image Error: %s\n", IMG_GetError());
            success = false;
        }
        else{
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
        if(!textTexture.loadFromRenderedText("Initialized!", textColor, imageRenderer)){
            printf("Failed to render text texture!\n");
            success = false;
        }
    }
    return success;
}

void refreshWindow(){
    SDL_RenderClear(imageRenderer);
    // renders the image itself
    imageTexture.renderTexture(imageRenderer);
    // renders the text (the FPS counter in this case)
    
    textTexture.loadFromRenderedText(std::to_string(getFPS()), textColor, imageRenderer);
    textTexture.renderSprite(0, 0, NULL, imageRenderer);
    SDL_RenderPresent(imageRenderer);

    int frameRemainingTicks = framesCapTimer.getTicks();
    if(frameRemainingTicks < 1000/60.f) SDL_Delay(1000/60.f - frameRemainingTicks);
    framesCapTimer.start();
}

float getFPS(){
    // uncommenting this will return FPS counting to get avgFPS through the entire runtime, avgFPS will change slowly.
    if(framesCount >= 150){
        // restart timer to get 0 ticks again
        framesCountTimer.start();
        framesCount = 0;
    }
    
    float avgFPS = framesCount/(framesCountTimer.getTicks()/1000.f);
    framesCount++;
    return avgFPS;
}

void quit(){
    //Free loaded images
    imageTexture.clearTexture();
    textTexture.clearTexture();

    TTF_CloseFont(umeboshiFont);
    umeboshiFont = NULL;

    //Destroy window
    SDL_DestroyRenderer(imageRenderer);
    SDL_DestroyWindow(window);
    window = NULL;
    imageRenderer = NULL;

    //Quit SDL subsystems
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}