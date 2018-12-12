#ifndef GAME_H
#define GAME_H

#define SCREEN_HEIGHT 600
#define SCREEN_WIDTH 480
#define SCALE 20

#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>



using namespace std;

// enum const for Game States
enum GameState{PLAY,EXIT};


class Game
{
    public:

        Game();
        virtual ~Game();
        void run();  // run program

        static SDL_Renderer *gameRenderer; // for all rendering on screen
        static TTF_Font *font;  //font of text
        static SDL_Texture *loadText(string,SDL_Color);      // loading Text as Texture
        static void fatalError(string,bool);    // handles all type of Program Errors

        static const int FPS=60;        // const Frames Per Seconds



    protected:

    private:

        bool initSystem();      // setup the system
        void cleanSystem();     // clean system and memory
        bool loadFiles();       // load program stuff
        void updateScreen();    // update changes on screen
        void renderChanges();   // render changes on screen
        void gameLoop();        // main Game-Loop
        void handleGameEvents();        // handles all events of program stuffs
        void renderScore();     // render updated score on screen
        void gameOver();        // handles program when game ends
        void waitForKBHit();    // waits program until KB-Hit

        SDL_Window *gameWindow; // game window
        SDL_Surface *gameSurface;       // surface of game
        SDL_Event gameEvents;   // event variable
        GameState gameState;    // store current state of game
        unsigned long long score; // stores score
};

#endif // GAME_H
