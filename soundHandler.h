#ifndef SOUNDHANDLER_H
#define SOUNDHANDLER_H

#include "Game.h"


class soundHandler
{
    public:
        soundHandler();
        virtual ~soundHandler();

        static Mix_Music *bgm;
        static Mix_Chunk *destruction;
        static Mix_Chunk *gameOver;
        static Mix_Chunk *movement;

        static bool loadAllSounds();
        static void freeAllSounds();
        static void playBGM();
        static void stopBGM();
        static void playDestructionEffect();
        static void playGameOverEffect();
        static void playMovementEffect();


    protected:

    private:
};

#endif // SOUNDHANDLER_H
