#ifndef _CTEXTURE_H_
#define _CTEXTURE_H_

// I should read up more on class access modifiers and how they can be included in the code.

class cTexture{
    public:
        cTexture();
        virtual ~cTexture();
        //Deallocates texture
        void destroyTexture();

        //Loads image at specified path
        bool loadPNG(std::string path);

        //Renders texture at given point
        void renderTexture(int x, int y, int w, int h, SDL_Rect* spriteClip, float angle, SDL_Point* centerPoint, SDL_RendererFlip flipState);

        void renderText(int x, int y, std::string text, TTF_Font* textFont, float angle, SDL_Point* centerPoint, SDL_RendererFlip flipState);

        void setTextColor(Uint8 r, Uint8 g, Uint8 b);

        int getWidth();
        int getHeight();

    protected:

    private:
        //The actual hardware texture
        SDL_Texture* texture;
        int textureWidth;
        int textureHeight;
        SDL_Color textColor;
};

#endif