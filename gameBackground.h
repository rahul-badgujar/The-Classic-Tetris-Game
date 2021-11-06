#ifndef GAMEBACKGROUND_H
#define GAMEBACKGROUND_H

#include "Game.h"


class gameBackground // class that handles stuff related to game background
{
    public:
        gameBackground();
        virtual ~gameBackground();

        bool loadBackground(std::string );  //load background
        void drawBackground(); // draw background
        void scrollBackground();  // scroll background

        static const int scrollSpeed=1;  // constant scrolling speed


    protected:

    private:
        SDL_Texture *backgroundTexture;  // background image texture
        SDL_Rect backgroundClip;  //  background image clip to be rendered on screen
};

#endif // GAMEBACKGROUND_H
