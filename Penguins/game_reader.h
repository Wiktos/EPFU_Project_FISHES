#pragma once
#include "game.h"

typedef struct GameReader GameReader;
struct GameReader
{
    Game* (*readGame)(char* inputFilePath);
    //TODO : Make structure for input Params and return them with this function temporary return void
    void (*readInputParams)(int, char**);
};

//reads game from input file function
static Game* readGame(char* inputFilePath)
{
    int numberOfPlayers = 2, availablePenguins = 1;
    Dimension boardDim;
    boardDim.row = 10;
    boardDim.col = 10;

    //1. Read first row from input file to the variables above

    Game* retGame = createGame(numberOfPlayers, boardDim);
    if(retGame == NULL)
        goto ErrorHandler;


     int* scores = (int*) calloc(numberOfPlayers, sizeof(int));

    //2. Read scores for every player to scores table

    int i;
    for(i = 0; i < numberOfPlayers; i++)
    {
        initPlayer(scores[i], availablePenguins, retGame->getPlayer(i, retGame));
    }

    //3. Read and initialize every field
    int currField = numberOfPlayers + 1; // +1 because we don't expect that value in input file so every validation function will return false


    return retGame;

ErrorHandler :
    perror("Error while reading game from input file");
    exit(EXIT_FAILURE);
}

//reads input parameters    TODO : CHANGE RETURN VALUE
static void readInputParams(int argc, char** argv)
{
    //do reading
    return /*PARAMS STRUCTURE*/;
}

//constructor
GameReader* createGameReader()
{
    GameReader* retv = (GameReader*) malloc(sizeof(GameReader));
    retv->readGame = &readGame;
    retv->readInputParams = &readInputParams;

    return retv;
}

//destructor
void finalizeGameReader(GameReader* reader)
{
    free(reader);
}
