#pragma once
#include "game.h"

typedef struct GameReader GameReader;
struct GameReader
{
    char* inputFilePath;
    Game* (*readGame)();
    //TODO : Make structure for input Params and return them with this function temporary return void
    void (*readInputParams)(int, char**);
};

//reads game from input file function
static Game* readGame()
{
    //reading and initializing values of player and field

    //temporary solution
    Dimension* boardDim = createDimension(4, 4);
    Game* retGame = createGame(3, *boardDim);

    return retGame;
}

//reads input parameters    TODO : CHANGE RETURN VALUE
static void readInputParams(int argc, char** argv)
{
    //do reading
    return /*PARAMS STRUCTURE*/;
}

//constructor
GameReader* createGameReader(char* path)
{
    GameReader retv;
    retv.inputFilePath = path;
    retv.readGame = &readGame;
    retv.readInputParams = &readInputParams;

    return (GameReader*)&retv;
}
