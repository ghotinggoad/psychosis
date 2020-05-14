#include "../include/global.h"

cTexture::cTexture(){
    texture = NULL;
    textureWidth = 0;
    textureHeight = 0;
}

cTexture::~cTexture(){
    clearTexture();
}

bool cTexture::loadFromFile(std::string texturePath, SDL_Renderer* gameRenderer){
    //Get rid of preexisting texture
    clearTexture();

    //The final texture
    SDL_Texture* newTexture = NULL;

    //Load image at specified path
    SDL_Surface* surfaceImageLoaded = IMG_Load( texturePath.c_str());
    if( surfaceImageLoaded == NULL){
        printf( "Unable to load image %s! SDL_image Error: %s\n", texturePath.c_str(), IMG_GetError());
    }
    else{
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(gameRenderer, surfaceImageLoaded);
        if(newTexture == NULL){
            printf( "Unable to create texture from %s! SDL Error: %s\n", texturePath.c_str(), SDL_GetError());
        }
        else{
            //Get image dimensions
            textureWidth = surfaceImageLoaded->w;
            textureHeight = surfaceImageLoaded->h;
        }
        //Get rid of old loaded surface
        SDL_FreeSurface(surfaceImageLoaded);
    }

    //Return success
    texture = newTexture;
    return texture != NULL;
}

bool cTexture::loadFromRenderedText(std::string textString, SDL_Color textColor, SDL_Renderer* imageRenderer){
    clearTexture();
    
    SDL_Surface* textSurface = TTF_RenderText_Solid(umeboshiFont, textString.c_str(), textColor);
    SDL_Texture* newTexture = NULL;

	if(textSurface == NULL)
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else
	{
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface(imageRenderer, textSurface);
		if(newTexture == NULL )
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			textureWidth = textSurface->w;
			textureHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
    
    texture = newTexture;

	//Return success
	return texture != NULL;
}

void cTexture::clearTexture(){
    //Free texture if it exists
    if(texture != NULL){
        SDL_DestroyTexture(texture);
        texture = NULL;
        textureWidth = 0;
        textureHeight = 0;
    }
}

void cTexture::renderTexture(SDL_Renderer* imageRenderer){
    SDL_RenderCopy(imageRenderer, texture, NULL, NULL);
}

void cTexture::renderSprite(int x, int y, SDL_Rect* spriteClip, SDL_Renderer* imageRenderer){
    //Set rendering space and render to screen
    SDL_Rect renderQuad = {x, y, textureWidth, textureHeight };
    if(spriteClip != NULL ){
        renderQuad.w = spriteClip->w;
        renderQuad.h = spriteClip->h;
    }
    SDL_RenderCopy(imageRenderer, texture, spriteClip, &renderQuad);
}

int cTexture::getWidth(){
    return textureWidth;
}

int cTexture::getHeight(){
    return textureHeight;
}