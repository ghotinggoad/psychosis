#ifndef CTEXTURE_H
#define CTEXTURE_H

class cTexture{
    public:
        cTexture();
        virtual ~cTexture();

        //Loads image at specified path
        bool loadFromFile(std::string path, SDL_Renderer* imageRenderer);

        bool loadFromRenderedText(std::string textString, SDL_Color textColor, SDL_Renderer* imageRenderer);

        //Deallocates texture
        void clearTexture();

        void renderTexture(SDL_Renderer* gameRenderer);

        //Renders texture at given point
        void renderSprite(int x, int y, SDL_Rect* clip, SDL_Renderer* gameRenderer);

        int getWidth();
        int getHeight();

    protected:

    private:
        //The actual hardware texture
        SDL_Texture* texture;
        int textureWidth;
        int textureHeight;
};

#endif