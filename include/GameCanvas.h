#ifndef GAMECANVAS_H
#define GAMECANVAS_H

#include "Game.h"
#include "Tiles.h"
#include "imageHandler.h"

#define CANVAS_ROWS 30
#define CANVAS_COLS 24
#define TET_ROWS  30
#define TET_COLS  15


class GameCanvas
{
    public:
        GameCanvas();
        virtual ~GameCanvas();

        void showMatrix();      // print canvas to screen
        bool checkForStopCondition(int block[4][4],int r,int c);    // check for stopping condition of a block
        bool destroyRows();                     // destroy rows
        void copyBlockToCanvas(int block[4][4],int r,int c);    // copy block to canvas
        void clearBlockFromCanvas(int block[4][4],int r,int c); // clears the block from canvas
        bool isLeftMovePossible(int block[4][4],int r,int c);   // is there left movement possible
        bool isRightMovePossible(int block[4][4],int r,int c);  // is there right movement possible
        bool unifyColor();      // make all placed block BLACK

    protected:

    private:
        int canvasMatrix[30][24];       // our canvas matrix
};

#endif // GAMECANVAS_H
