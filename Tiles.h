#ifndef TILES_H
#define TILES_H

#include "Game.h"

#define TILE_GREEN 1
#define TILE_RED 2
#define TILE_BLACK 3
#define TILE_BLUE 4
#define TILE_ORANGE 5
#define TILE_VOILET 6
#define TOTAL_TILES 7
#define TILE_DIM 20

class Tiles
{
    public:
        Tiles();
        virtual ~Tiles();

        static SDL_Rect tilesSrcRects[TOTAL_TILES];

    protected:

    private:
};

#endif // TILES_H
