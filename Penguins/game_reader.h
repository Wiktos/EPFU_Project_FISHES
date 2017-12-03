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

bool checkNumberOfPlayers(int);
bool checkNumberOfPenguins(int, int);
bool checkDimmension(int);
bool checkScoreOfPlayer(int, int);
bool checkFieldProperty(int, int);

//reads game from input file function
static Game* readGame(char* inputFilePath)
{
    int numberOfPlayers = 2, availablePenguins = 1, sumOfScores = 0;
    int temp, i, j, scoreTemp;
    Dimension boardDim;
    boardDim.row = 10;
    boardDim.col = 10;
    FILE * filePointer;
    filePointer = fopen("input_file.txt", "r");


    //1. Read first row from input file to the variables above

    Game* retGame = createGame(numberOfPlayers, boardDim);
    if(retGame == NULL)
        goto ErrorHandler;

    if (fscanf(filePointer, "%d", &numberOfPlayers) != 1)
        goto ErrorHandler;

    else if(checkNumberOfPlayers(numberOfPlayers) == false)
	goto ErrorHandler;

    if (fscanf(filePointer, "%d", &availablePenguins) != 1)
        goto ErrorHandler;

    if (fscanf(filePointer, "%d", &boardDim.row) != 1)
	goto ErrorHandler;

    else if(checkDimmension(boardDim.row) == false)
	goto ErrorHandler;

    if (fscanf(filePointer, "%d", &boardDim.col) != 1)
	goto ErrorHandler;

    else if(checkDimmension(boardDim.col) == false)
	goto ErrorHandler;

    temp = boardDim.com * boardDim.row;

    if(checkNumberOfPenguins(availablePenguins, temp) == false)
	goto ErrorHandler;

    int x = feof(filePointer) ? EOF : 0;
    while (x != EOF && x != '\n') x = fgetc(filePointer);


    int* scores = (int*) calloc(numberOfPlayers, sizeof(int));

    //2. Read scores for every player to scores table

    for(i = 0; i < numberOfPlayers; i++){
        if (fscanf(filePointer, "%d", &score[i]) != 1)
            goto ErrorHandler;

        sumOfScore += score[i];
        scoreTemp = score[i];

        else if(checkScoreOfPlayer(scoreTemp, sumOfScore) == false)
            goto ErrorHandler;
    }

    for(i = 0; i < numberOfPlayers; i++)
    {
        initPlayer(scores[i], availablePenguins, retGame->getPlayer(i, retGame));
    }

    //3. Read and initialize every field
    int currField = numberOfPlayers + 1; // +1 because we don't expect that value in input file so every validation function will return false

	for(i = 0; i < numberOfRows; i++){
        for(j = 0; j < numberOfColumns; j++){
            if (fscanf(filePointer, "%d", &currField) != 1)
                goto ErrorHandler;

            else if (checkFieldProperty(currField, numberOfPlayers) == false)
                goto ErrorHaldner;

        }

    }

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

bool checkNumberOfPlayers(int n){
	if(n<2) return false;
	else return true;
}

bool checkNumberOfPenguins(int n, int k)
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



