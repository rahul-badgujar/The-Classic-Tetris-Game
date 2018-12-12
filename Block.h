#ifndef BLOCK_H
#define BLOCK_H

#include "Game.h"


class Block
{
    public:
        Block();
        virtual ~Block();

        int blockPattern[4][4]; // stores pattern of our block

        void createNewBlock(int r,int c);       // create a new and random block
        void rotateBlock();     // rotate the block
        void moveBlockDown();   // move the block down
        void moveBlockHoriz(int dir);   // move block horizontally in accordance with the direction provided

        // getters and setters
        int getRowNo();
        int getColNo();
        void setRowNo(int);
        void setColNo(int);
        int getTileType();
        void setTileType(int);

        // assignment = operator overloaded
        void operator = (const Block &src)
        {
            tileType=src.tileType;
            rowNo=src.rowNo;   colNo=src.colNo;

            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    blockPattern[i][j]=src.blockPattern[i][j];
                }
            }
        }

    protected:

    private:
        int rowNo,colNo;        // store row and column number of block
        int tileType;   // and its tiletype
};


#endif // BLOCK_H
