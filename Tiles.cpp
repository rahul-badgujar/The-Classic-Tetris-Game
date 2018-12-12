#include "Tiles.h"

SDL_Rect Tiles::tilesSrcRects[TOTAL_TILES]={
                                        {-100,-100,TILE_DIM,TILE_DIM},  // none of use
                                        {174,107,TILE_DIM,TILE_DIM},
                                        {75,148,TILE_DIM,TILE_DIM},
                                        {116,0,TILE_DIM,TILE_DIM},
                                        {265,132,TILE_DIM,TILE_DIM},
                                        {0,172,TILE_DIM,TILE_DIM},
                                        {265,445,TILE_DIM,TILE_DIM}
                                    };

Tiles::Tiles()
{
    //ctor
}

Tiles::~Tiles()
{
    //dtor
}
