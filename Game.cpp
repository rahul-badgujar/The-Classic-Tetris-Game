
#include "GameCanvas.h"
#include "Block.h"
#include "soundHandler.h"

// two blocks we use in program
Block currentBlock; // stores the current moving block
Block nextBlock;    // stores the next upcoming block

GameCanvas canvas;  // basically a 2-D matrix, stores our game

Game::Game()
{
    //ctor init default values
    gameSurface=nullptr;   gameWindow=nullptr;

    gameState=PLAY;

    score=0;

    // seed value to gen random numbers
    srand(time(NULL));
}

Game::~Game()
{
    //dtor init to nullptr after freeing memory
    gameSurface=nullptr;    gameRenderer=nullptr;
    gameWindow=nullptr;   font=nullptr;
}

// static members, declared inside class, defined outside class
SDL_Renderer *Game::gameRenderer=nullptr;
TTF_Font *Game::font=nullptr;

void Game::fatalError(string error,bool closeProgram)
{
    cout<<"Error Occured : "<<error<<endl; // if closeProgram is true, cleansystem and exit
    if(closeProgram)
    {
        Game g; // since it is a static member function, we need object to call non-static member functions
        g.cleanSystem();
        cin.get();
        exit(-1);
    }
}

// load given text with given color
SDL_Texture* Game::loadText(string text,SDL_Color color)
{
    SDL_Surface *textSurface=TTF_RenderText_Solid(Game::font,text.c_str(),color); // load text on surface
    SDL_Texture *ret=SDL_CreateTextureFromSurface(gameRenderer,textSurface);    // convert surface to texture
    SDL_FreeSurface(textSurface);   textSurface=nullptr;    // free the surface, now none of use
    return ret;     // return the text as texture
}


void Game::run()
{
    if(!initSystem())   // init system and libraries
    {
        cout<<"Error in INITIALIZING System "<<endl; cin.get(); return;
    }
    if(!loadFiles())    // load files and allocate memory
    {
        cout<<"Error in Loading Files "<<endl;  cin.get();  return;
    }

    // show title screen
    imageHandler::showImage(imageHandler::titleScreenTexture,nullptr,nullptr);
    renderChanges();
    SDL_Delay(1000);

    // show game instructions
    imageHandler::showImage(imageHandler::howToPlayTexture,nullptr,nullptr);
    renderChanges();

    gameState=PLAY;     // let the game begins

    waitForKBHit(); // wait while any key is pressed

    while(gameState==PLAY)
    {
        gameLoop(); // as we don't have menu, it's quite simple as it is
    }


    cleanSystem();  // clean the system, and end program
}

// init SDL and its extensions
bool Game::initSystem()
{
    SDL_Init(SDL_INIT_EVERYTHING); // init common SDL stuff
    IMG_Init(IMG_INIT_PNG);     // init SDL_Image
    TTF_Init();     // init SDL True Type Font
    Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,2,2048);     // init SDL_Mixer to manage audio

    // create window, attach surface and renderer to it, and set default  render draw color
    gameWindow=SDL_CreateWindow("The Classic Tetris Game",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    gameSurface=SDL_GetWindowSurface(gameWindow);
    gameRenderer=SDL_CreateRenderer(gameWindow,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(gameRenderer,255,255,255,255);

    return true;    // as I have all libraries set up, I simply return true
}

void Game::cleanSystem()
{
    // deallocate all heap memory allocated for game objects
    SDL_FreeSurface(gameSurface);
    SDL_DestroyRenderer(gameRenderer);
    TTF_CloseFont(font);
    SDL_DestroyWindow(gameWindow);
    imageHandler::freeAllMemory();
    soundHandler::freeAllSounds();

    // turn SDL and its extensions off
    Mix_Quit();  TTF_Quit();  IMG_Quit();  SDL_Quit();
}

// load all files and allocate memory accordingly
bool Game::loadFiles()
{
    font=TTF_OpenFont("assets/fonts/neuropol.ttf",28);
    // if files are misplaced, and could not be found, terminate by prompting the same on console
    if(!font || !imageHandler::loadAllImages() || !soundHandler::loadAllSounds())
        return false;
    return true;
}

// handle all game events
void Game::handleGameEvents()
{
    while(SDL_PollEvent(&gameEvents)) // while there are events in queue
    {
        switch(gameEvents.type) // handle event according to its type
        {
            case SDL_QUIT : // if X button of window pressed
                gameState=EXIT; // game state is EXIT
                break;
            case SDL_KEYDOWN:   // handle keyboard events
                if(gameEvents.key.keysym.sym==SDLK_SPACE) // space bar for rotating the block
                {
                    // clear the position of block form canvas
                    canvas.clearBlockFromCanvas(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo());
                    // then rotate block
                    currentBlock.rotateBlock();
                }
                else if(gameEvents.key.keysym.sym==SDLK_s) // s for down motion
                {
                    // if u want block to fall down in steps

                    // clear block from canvas
                    canvas.clearBlockFromCanvas(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo());
                    // if there is no collision happening
                    if(!canvas.checkForStopCondition(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo()))
                    {
                        soundHandler::playMovementEffect(); // play the block movement sound effect
                        int newRow=currentBlock.getRowNo(); // getter gives private info
                        newRow++;                           // increase the row number of block
                        currentBlock.setRowNo(newRow);  // setter set incremented row no
                    }

                    // if u want block to direct fall down

                    // do increment row no till collision happens
                    /*
                    while(!canvas.checkForStopCondition(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo()))
                    {
                        // clear block position form canvas
                        canvas.clearBlockFromCanvas(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo());
                        // increment row no
                        int newRow=currentBlock.getRowNo();
                        newRow++;
                        currentBlock.setRowNo(newRow);
                    }*/
                }
                else if(gameEvents.key.keysym.sym==SDLK_LEFT)  // a to move block left
                {
                    // clear block from canvas
                    canvas.clearBlockFromCanvas(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo());
                    // only move block to left if there is chance of moving
                    if(canvas.isLeftMovePossible(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo()))
                        currentBlock.moveBlockHoriz(0); // 0 passed as argument to indicate left movement
                }
                else if(gameEvents.key.keysym.sym==SDLK_RIGHT)
                {
                    // clear block from canvas
                    canvas.clearBlockFromCanvas(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo());
                    // only move block to right if there is chance of moving
                    if(canvas.isRightMovePossible(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo()))
                        currentBlock.moveBlockHoriz(1); // 1 indicates right movement of block
                }
                break;
        }
    }
}
void Game::updateScreen()
{
    // clear the screen by making the background white
    SDL_SetRenderDrawColor(gameRenderer,255,255,255,255);
    SDL_RenderClear(gameRenderer);

    // render the background image
    imageHandler::showImage(imageHandler::bkTexture,nullptr,nullptr);

    // clear both, current and next block from canvas
    canvas.clearBlockFromCanvas(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo());
    canvas.clearBlockFromCanvas(nextBlock.blockPattern,nextBlock.getRowNo(),nextBlock.getColNo());

    // move our current block down as its default motion
    currentBlock.moveBlockDown();

    // copy our block pattern on canvas
    canvas.copyBlockToCanvas(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo());
    // check for collision
    if(canvas.checkForStopCondition(currentBlock.blockPattern,currentBlock.getRowNo(),currentBlock.getColNo()))
    {
        score+=5;   // give +5 score if the block is placed
        if(canvas.unifyColor()) // check for the game over condition
        {
            canvas.showMatrix();    // show current canvas status
            SDL_Delay(1000);
            gameState=EXIT;     // make the game ends here
            return;     // no need to do any other stuff of updating, return function from here
        }
        while(canvas.destroyRows())    // check if there is availability of destroying rows
        {
            soundHandler::playDestructionEffect();  // play sound effect for row destruction
            score+=20;      // +20 score if a row destroys
        }
        currentBlock=nextBlock; // make the next block as current block
        currentBlock.setRowNo(0);  currentBlock.setColNo(4);    // reset position of current block
        nextBlock.createNewBlock(23,18);    // create a new next block
    }

    // copy our next block pattern to canvas
    canvas.copyBlockToCanvas(nextBlock.blockPattern,nextBlock.getRowNo(),nextBlock.getColNo());

    // show our canvas
    canvas.showMatrix();

    // display score on screen
    renderScore();

}

void Game::renderChanges()
{
    SDL_RenderPresent(gameRenderer);    // apply all changes on screen
}

// main game loop
void Game::gameLoop()
{
    soundHandler::playBGM();    // start BGM
    score=0;        // init score to 0
    // create two blocks of game
    currentBlock.createNewBlock(0,4);
    nextBlock.createNewBlock(23,18);
    while(gameState==PLAY)
    {
        Uint32 startTime=SDL_GetTicks();    // stuff to maintain const framerate

        handleGameEvents(); // handle all game events
        updateScreen();     // make changes accordingly on screen
        renderChanges();    // render all changes on screen

        // stuff for maintaining constant framerate
        Uint32 frameTime=SDL_GetTicks()-startTime;
        if(frameTime<1000/FPS)
            SDL_Delay(1000/FPS-frameTime);
    }
    soundHandler::stopBGM();    // stop BGM
    gameOver(); // handle the game over scene
}

// handles score board on game screen
void Game::renderScore()
{
    stringstream scoreStr;  // stringsteam used for score
    scoreStr<<" "<<score<<" ";
    SDL_Color textColor={0,0,0,255};
    if(imageHandler::text)
    {
        // deallocate memory for previous text, if exist
        SDL_DestroyTexture(imageHandler::text);   imageHandler::text=nullptr;
    }
    // render score on screen
    imageHandler::text=loadText(scoreStr.str().c_str(),textColor);
    SDL_Rect scoreBoard={340,110,440-340,150-110};
    imageHandler::showImage(imageHandler::text,nullptr,&scoreBoard);

}

void Game::gameOver()
{
    soundHandler::playGameOverEffect(); // play game over sound effect
    imageHandler::showImage(imageHandler::transparentTexture,nullptr,nullptr);  // make background transparent

    // show game over image
    SDL_Rect gameOverRect={40,120,440-40,380-120};
    imageHandler::showImage(imageHandler::gameOverTexture,nullptr,&gameOverRect);

    // render final score on screen
    stringstream scoreStr;
    scoreStr<<" SCORE : "<<score<<" ";
    SDL_Color textColor={255, 255, 0,255};
    if(imageHandler::text)
    {
        // deallocate memory for previous text, if exist
        SDL_DestroyTexture(imageHandler::text);   imageHandler::text=nullptr;
    }
    imageHandler::text=loadText(scoreStr.str().c_str(),textColor);
    SDL_Rect scoreBoard={80,400,400-80,480-400};
    imageHandler::showImage(imageHandler::text,nullptr,&scoreBoard);

    renderChanges();

    // wait until user close the program using X button on window
    SDL_Event ev;
    bool finalEnd=false;
    while(!finalEnd)
    {
        while(SDL_PollEvent(&ev))
        {
            if(ev.type==SDL_QUIT)
                finalEnd=true;
        }
    }
}

void Game::waitForKBHit()
{
    bool cont=false;
    // wait while there is a key pressed, or the program is closed
    while(!cont)
    {
        while(SDL_PollEvent(&gameEvents))
        {
            if(gameEvents.type==SDL_KEYDOWN)
               cont=true;
            else if(gameEvents.type==SDL_QUIT)
            {
                cont=true;
                gameState=EXIT;
            }
        }
    }
}


