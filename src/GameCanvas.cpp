#include "GameCanvas.h"

GameCanvas::GameCanvas()
{
    //ctor set default matrix
    for(int i=0;i<CANVAS_ROWS;i++)
        for(int j=0;j<CANVAS_COLS;j++)
            canvasMatrix[i][j]=0;
}

GameCanvas::~GameCanvas()
{
    //dtor
}

void GameCanvas::showMatrix()
{
    for(int i=0;i<CANVAS_ROWS;i++)
    {
        for(int j=0;j<CANVAS_COLS;j++)
        {
            if(canvasMatrix[i][j]!=0) // if there is a tile present
            {
                // show that tile on screen in canvas
                SDL_Rect dest={j*TILE_DIM,i*TILE_DIM,TILE_DIM,TILE_DIM};
                if(imageHandler::tilesTexture==nullptr)
                    cout<<"HELLO";
                imageHandler::showImage(imageHandler::tilesTexture,&Tiles::tilesSrcRects[canvasMatrix[i][j]],&dest);
            }
        }
    }
}
void GameCanvas::copyBlockToCanvas(int block[4][4],int r,int c)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(block[i][j]!=0)  // only copy the pattern, and not 0's from pattern
            {

                canvasMatrix[r+i][c+j]=block[i][j]; // canvas matrix has indices relative to block position
            }
        }
    }
}
void GameCanvas::clearBlockFromCanvas(int block[4][4],int r,int c)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(block[i][j]!=0)  // only cleat the tile elements
                canvasMatrix[r+i][c+j]=0;
        }
    }
}

bool GameCanvas::checkForStopCondition(int block[4][4],int r,int c)
{
    bool collided=false;
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(block[i][j]!=0)  // if its a valid tile of block
            {
                // if it has reached bottom or black tile is beneath it
                if(r+i>=29 || (canvasMatrix[r+i+1][j+c]==1))
                    collided=true;
            }
        }
    }
    return collided;
}
bool GameCanvas::unifyColor()
{
    bool isTouhedUp=false;
    for(int i=0;i<CANVAS_ROWS;i++)
    {
        for(int j=0;j<CANVAS_COLS;j++)
        {
            if(canvasMatrix[i][j]!=0)
            {
                canvasMatrix[i][j]=1;
                if(i==0)        // check if tetris is full
                    isTouhedUp=true;
            }
        }
    }
    return isTouhedUp;
}
bool GameCanvas::destroyRows()
{
    bool isRowDestroyed=false;
    for(int i=TET_ROWS-1;i>=1;i--)
    {
        int filledTiles=0;
        for(int j=0;j<TET_COLS;j++)
        {
            if(canvasMatrix[i][j]==1)
                filledTiles++;  // count no. of BLACK tiles in a row
        }
        if(filledTiles==TET_COLS)   // if BLACK tiles are equal to tetris total columns
        {
            // move all rows down
            for(int a=i;a>=1;a--)
            {
                for(int b=0;b<TET_COLS;b++)
                    canvasMatrix[a][b]=canvasMatrix[a-1][b];
            }
            // make the uppermost row full of 0
            for(int c=0;c<TET_COLS;c++)
                canvasMatrix[0][c]=0;

            isRowDestroyed=true;
            break;
        }
    }
    return isRowDestroyed;
}
bool GameCanvas::isLeftMovePossible(int block[4][4],int r,int c)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(block[i][j]!=0)  // if the block tile, touches the boundry or touches a black tile, restrict movement
            {
                if(canvasMatrix[r+i][c+j-1]==1 || c+j==0)
                    return false;
            }
        }
    }
    return true;
}
bool GameCanvas::isRightMovePossible(int block[4][4],int r,int c)
{
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            if(block[i][j]!=0)  // if a valid tile
            {
                if(canvasMatrix[r+i][c+j+1]==1 || c+j==TET_COLS-1)  // goes out of boundry or collide with black tile, restrict movement
                    return false;
            }
        }
    }
    return true;
}
