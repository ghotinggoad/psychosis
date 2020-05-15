#include "../include/global.h"

cTexture::cTexture(){
    texture = NULL;
    textureWidth = 0;
    textureHeight = 0;
    textColor = {255, 255, 255, 255};
    SDL_Color keyColor;
}

cTexture::~cTexture(){
    destroyTexture();
}

void cTexture::destroyTexture(){
    //free up texture
    if(texture != NULL){
        SDL_DestroyTexture(texture);
        texture = NULL;
        textureWidth = 0;
        textureHeight = 0;
        textColor = {0, 0, 0, 0};
    }
}

bool cTexture::loadPNG(std::string filePath){
    // renew texture
    destroyTexture();
    // load image into temporary surface
    SDL_Surface* imageSurfaceTemp = IMG_Load(filePath.c_str());
    // get image dimensions
    textureWidth = imageSurfaceTemp -> w;
    textureHeight = imageSurfaceTemp -> h;
    // render surface (unoptimized) to texture (optimized data after hardware acceleration)
    texture = SDL_CreateTextureFromSurface(renderer, imageSurfaceTemp);
    if(imageSurfaceTemp == NULL) printf("SDL_image failed to load image from %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
    if(texture == NULL) printf("Unable to create texture from %s! SDL Error: %s\n", filePath.c_str(), SDL_GetError());
    SDL_FreeSurface(imageSurfaceTemp);
    return texture != NULL;
}

void cTexture::renderTexture(int x, int y, int w, int h, SDL_Rect* spriteClip){
    // sets coordinates to target renderer as well as texture dimensions
    SDL_Rect renderTarget = {x, y, w/(1280/SCREEN_WIDTH), h/(960/SCREEN_HEIGHT)};
    if(spriteClip != NULL ){
        renderTarget.w = spriteClip -> w/(1280/SCREEN_WIDTH);
        renderTarget.h = spriteClip -> h/(960/SCREEN_HEIGHT);
    }
    // Copies texture onto renderer with options for "clip data" and basic image transformation.
    SDL_RenderCopyEx(renderer, texture, spriteClip, &renderTarget, 0.0, NULL, SDL_FLIP_NONE);
}

void cTexture::renderText(int x, int y, std::string text, TTF_Font* textFont){
    // TTF_SetFontStyle 
    destroyTexture();
    // load UTF8 string into temporary surface
    SDL_Surface* textSurfaceTemp = TTF_RenderUTF8_Solid(textFont, text.c_str(), textColor);
    texture = SDL_CreateTextureFromSurface(renderer, textSurfaceTemp);
    textureWidth = textSurfaceTemp -> w;
    textureHeight = textSurfaceTemp -> h;
    SDL_Rect renderQuad = {x, y, textureWidth, textureHeight};
    SDL_RenderCopyEx(renderer, texture, NULL, &renderQuad, 0.0, NULL, SDL_FLIP_NONE);
}

void cTexture::setTextColor(int r, int g, int b, int a){
    textColor.r = r;
    textColor.g = g;
    textColor.b = b;
    textColor.a = a;
}

int cTexture::getWidth(){
    return textureWidth;
}

int cTexture::getHeight(){
    return textureHeight;
}