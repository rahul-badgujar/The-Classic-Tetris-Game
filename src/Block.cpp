#include "Block.h"
#include "soundHandler.h"
#include "GameCanvas.h"

// seven block patterns
int blockPatterns[7][4][4]=
    {
        {
            // I
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        {
            // O
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            // T
            {0,0,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,1,0,0}
        },
        {
            // L
            {0,0,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0}
        },
        {
            // L-Mirrored
            {0,0,0,0},
            {0,0,1,0},
            {0,0,1,0},
            {0,1,1,0}
        },
        {
            // Z
            {0,0,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,1,0}
        },
        {
            // Z-Mirrored
            {0,0,0,0},
            {0,0,1,0},
            {0,1,1,0},
            {0,1,0,0}
        }
    };



Block::Block()
{
    //ctor init defaults
    tileType=rowNo=colNo=0;
}

Block::~Block()
{
    //dtor
}

// creates a new and random block
void Block::createNewBlock(int r,int c)
{
    int pattern=rand()%7;   // chose a random pattern of block
    tileType=rand()%5+2;    // chose a random tile-type
    rowNo=r;   colNo=c; // position it on given positions

    // copy the pattern to block-pattern, and make all 1's of pattern to tile-type
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            blockPattern[i][j]=blockPatterns[pattern][i][j]*tileType;
        }
    }
}
void Block::rotateBlock()
{
    soundHandler::playMovementEffect(); // play the movement effect
    int copyBlock[4][4];    // dummy block

    // copy blockpattern in dummy block
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            copyBlock[i][j]=blockPattern[i][j];
        }
    }

    // change blockpattern to rotated block
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            blockPattern[i][j]=copyBlock[j][4-1-i];
        }
    }

    // if block went out of game boundry after rotating, handle it
    if(colNo<0)
    {
        colNo=0;
        int minC=5;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(blockPattern[i][j]>0)
                {
                    if(j<minC)
                        minC=j;
                }
            }
        }
        colNo-=minC;
    }
    else if(colNo+4>TET_COLS-1)
    {
        colNo=TET_COLS-1-4;
        int maxC=0;
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                if(blockPattern[i][j]>0)
                {
                    if(j>=maxC)
                    {
                        maxC=j;
                    }
                }
            }
        }
        maxC=3-maxC;
        colNo+=maxC;

    }
}
void Block::moveBlockDown()
{
    static unsigned long long int i=0;
    if(i++%40==0)   // to make the movement slower
    {
        soundHandler::playMovementEffect(); // play block movement effect
        rowNo++;                // move the block down
    }
}
void Block::moveBlockHoriz(int dir)
{
    soundHandler::playMovementEffect(); // movement sound effect
    if(dir==0)  // for left movement
    {
            colNo--;
    }
    else if(dir==1)     // for right movement
    {
            colNo++;
    }
}

// defination for getters and setters
int Block::getRowNo()
{
    return rowNo;
}
int Block::getColNo()
{
    return colNo;
}
void Block::setRowNo(int r)
{
    rowNo=r;
}
void Block::setColNo(int c)
{
    colNo=c;
}
int Block::getTileType()
{
    return tileType;
}
void Block::setTileType(int type)
{
    tileType=type;
}
