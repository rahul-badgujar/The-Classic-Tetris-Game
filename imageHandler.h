#ifndef IMAGEHANDLER_H
#define IMAGEHANDLER_H

#include "Game.h"


class imageHandler
{
    public:
        imageHandler();
        virtual ~imageHandler();

        // pointers to store memory for images, all static
        static SDL_Texture *tilesTexture;
        static SDL_Texture *bkTexture;
        static SDL_Texture *text;
        static SDL_Texture *transparentTexture;
        static SDL_Texture *gameOverTexture;
        static SDL_Texture *howToPlayTexture;
        static SDL_Texture *titleScreenTexture;

        // functions of imagehandler class, all static
        static bool loadAllImages();    // load all image files
        static void freeAllMemory();    // free allocated memory
        static SDL_Texture *loadTexture(string,int,int,int);    // load image as texture
        static void showImage(SDL_Texture*,SDL_Rect*,SDL_Rect*);        // show image clip on specified position

    protected:

    private:

};

#endif // IMAGEHANDLER_H
