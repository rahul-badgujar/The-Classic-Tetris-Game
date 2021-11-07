#include "soundHandler.h"

soundHandler::soundHandler()
{
    //ctor
}

soundHandler::~soundHandler()
{
    //dtor
}

Mix_Music *soundHandler::bgm=nullptr;
Mix_Chunk *soundHandler::destruction=nullptr;
Mix_Chunk *soundHandler::gameOver=nullptr;
Mix_Chunk *soundHandler::movement=nullptr;

bool soundHandler::loadAllSounds()
{
    bgm=Mix_LoadMUS("assets/music/tetrisBGM.mp3");
    destruction=Mix_LoadWAV("assets/music/destructionEffect.wav");
    movement=Mix_LoadWAV("assets/music/movementEffect.wav");
    gameOver=Mix_LoadWAV("assets/music/gameOverEffect.wav");

    if(!bgm || !destruction || !movement || !gameOver)
        return false;

    return true;
}
void soundHandler::freeAllSounds()
{
    Mix_FreeChunk(destruction);  destruction=nullptr;
    Mix_FreeChunk(gameOver);  gameOver=nullptr;
    Mix_FreeChunk(movement);  movement=nullptr;
    Mix_FreeMusic(bgm);  bgm=nullptr;
}

void soundHandler::playBGM()
{
    if(!Mix_PlayingMusic())
        Mix_PlayMusic(bgm,-1);
}
void soundHandler::stopBGM()
{
    if(Mix_PlayingMusic())
        Mix_HaltMusic();
}
void soundHandler::playDestructionEffect()
{
    Mix_PlayChannel(-1,destruction,0);
}
void soundHandler::playGameOverEffect()
{
    Mix_PlayChannel(-1,gameOver,0);
}
void soundHandler::playMovementEffect()
{
    Mix_PlayChannel(-1,movement,0);
}
