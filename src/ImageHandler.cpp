#include "imageHandler.h"
#include <SDL2/SDL_image.h>

imageHandler::imageHandler()
{
    //ctor
}

imageHandler::~imageHandler()
{
    //dtor
}


// static members, declared inside class, defined outside the class
SDL_Texture *imageHandler::tilesTexture=nullptr;
SDL_Texture *imageHandler::bkTexture=nullptr;
SDL_Texture *imageHandler::text=nullptr;
SDL_Texture *imageHandler::transparentTexture=nullptr;
SDL_Texture *imageHandler::gameOverTexture=nullptr;
SDL_Texture *imageHandler::howToPlayTexture=nullptr;
SDL_Texture *imageHandler::titleScreenTexture=nullptr;

// loads image as texture
SDL_Texture* imageHandler::loadTexture(string path,int r,int g,int b)
{
    SDL_Surface *tempImgSurface=IMG_Load(path.c_str()); // create image on surface
    SDL_Texture *retTexture=nullptr;    // texture to be returned
    if(tempImgSurface==nullptr) // if image does not loaded
    {
        Game::fatalError("Images at "+path+" not found",true);
    }
    else
    {
        SDL_SetColorKey(tempImgSurface,SDL_TRUE,SDL_MapRGB(tempImgSurface->format,r,g,b));  // set provided colorkey to surface
        retTexture=SDL_CreateTextureFromSurface(Game::gameRenderer,tempImgSurface); // convert surface to texture
        SDL_FreeSurface(tempImgSurface);   tempImgSurface=nullptr;  // deallocate the non-needed surface
    }
    return retTexture;  // return image consisting texture
}

bool imageHandler::loadAllImages()
{
    // load all image files
    tilesTexture=loadTexture("assets/images/Tiles.png",255,255,255);
    bkTexture=loadTexture("assets/images/gameBackground.png",255,255,255);
    transparentTexture=loadTexture("assets/images/transparent.png",255,255,255);
    gameOverTexture=loadTexture("assets/images/gameOver.png",0,0,0);
    howToPlayTexture=loadTexture("assets/images/howToPlay.png",0,0,255);
    titleScreenTexture=loadTexture("assets/images/title.png",0,0,255);

    // make the transparent texture
    SDL_SetTextureBlendMode(transparentTexture,SDL_BLENDMODE_BLEND);
    SDL_SetTextureAlphaMod(transparentTexture,130);

    // check if images loaded or not
    if(!tilesTexture || !bkTexture || !transparentTexture || !gameOverTexture || !howToPlayTexture || !titleScreenTexture)
        return false;
    return true;
}

void imageHandler::showImage(SDL_Texture* resourceTexture,SDL_Rect* src,SDL_Rect* dst)
{
    SDL_RenderCopy(Game::gameRenderer,resourceTexture,src,dst); // copy image on screen at specified position
}

void imageHandler::freeAllMemory()
{
    // deallocate all the dynamically allocated memory , avoid memory leak
    SDL_DestroyTexture(text);   text=nullptr;
    SDL_DestroyTexture(tilesTexture);   tilesTexture=nullptr;
    SDL_DestroyTexture(bkTexture);   bkTexture=nullptr;
    SDL_DestroyTexture(gameOverTexture);   gameOverTexture=nullptr;
    SDL_DestroyTexture(howToPlayTexture);   howToPlayTexture=nullptr;
    SDL_DestroyTexture(titleScreenTexture);   titleScreenTexture=nullptr;
}
