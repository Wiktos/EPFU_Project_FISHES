#pragma once
#include "game.h"
#include <stdbool.h>

typedef struct GameReader GameReader;
struct GameReader
{
    Game* (*readGame)(char* inputFilePath);
    //TODO : Make structure for input Params and return them with this function temporary return void
    void (*readInputParams)(int, char**);
};

//----------------------------------------------------------------------------

//reads game from input file function
static bool checkNumberOfPlayers(int);
static bool checkNumberOfPenguins(int, int);
static bool checkDimmension(int);
static bool checkScoreOfPlayer(int, int);
static bool checkFieldProperty(int, int);

static bool readScores(int* destination, int numOfPlayers, FILE* file)
{
    int i, sumOfScore = 0;
    for(i = 0; i < numOfPlayers; i++)
    {
        if (fscanf(file, "%d", &destination[i]) != 1)
            return false;

        sumOfScore += destination[i];

        if(checkScoreOfPlayer(destination[i], sumOfScore) == false)
            return false;
    }

    return true;
}

static bool readFields(Game* game, FILE* file)
{
    int i, j, currField = game->numberOfPlayers + 1; // +1 because we don't expect that value in input file so every validation function will return false
    Dimension boardDim = game->boardDimension;

	for(i = 0; i < boardDim.row; i++)
	{
           for(j = 0; j < boardDim.col; j++)
            {
              if(fscanf(file,"%d",&currField) != 0 || checkFieldProperty(currField, game->numberOfPlayers) == true)
              {
                initField(currField, game->getField(i, j, game));
              }
              else
                return false;

            }
    }

    return true;
}

//----------------------------------------------------------------------------

static Game* readGame(char* inputFilePath)
{
    int numberOfPlayers, availablePenguins;
    int i;
    Dimension boardDim;

    FILE * filePointer;
    filePointer = fopen(inputFilePath, "r");

    //1. Read first row from input file to the variables above
    if (fscanf(filePointer, "%d", &numberOfPlayers) != 1 || checkNumberOfPlayers(numberOfPlayers) == false)
        goto ErrorHandler;

    if (fscanf(filePointer, "%d", &availablePenguins) != 1)
        goto ErrorHandler;

    if (fscanf(filePointer, "%d", &boardDim.row) != 1 || checkDimmension(boardDim.row) == false)
        goto ErrorHandler;

    if (fscanf(filePointer, "%d", &boardDim.col) != 1 || checkDimmension(boardDim.col) == false)
        goto ErrorHandler;

    Game* retGame = createGame(numberOfPlayers, boardDim);
    if(retGame == NULL)
        goto ErrorHandler;

    if(checkNumberOfPenguins(availablePenguins, boardDim.col * boardDim.row) == false)
    {
        finalizeGame(retGame);
        goto ErrorHandler;
    }

    int* scores = (int*) calloc(numberOfPlayers, sizeof(int));

    //2. Read scores for every player to scores table
    bool result = readScores(scores, numberOfPlayers, filePointer);
    if(!result)
        goto ErrorHandler;

    for(i = 0; i < numberOfPlayers; i++)
    {
        initPlayer(scores[i], availablePenguins, retGame->getPlayer(i, retGame));
    }

    free(scores);

    //3. Read and initialize every field
    result = readFields(retGame, filePointer);

     fclose(filePointer);

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
void initGameReader(GameReader* reader)
{
    reader->readGame = &readGame;
    reader->readInputParams = &readInputParams;
}

bool checkNumberOfPlayers(int n){
	if(n<2) return false;
	else return true;
}

bool checkNumberOfPenguins(int n, int k){
	if(n>=k) return false;
	else return true;
}

bool checkDimmension(int n){
	if(n<2) return false;
	else return true;
}

bool checkScoreOfPlayer(int score, int sum){
	if((score<0)||(score>sum)) return false;
	else return true;
}

bool checkFieldProperty(int field, int n){
	if((field>3)||(field<(-1)*n)) return false;
	else return true;
}

