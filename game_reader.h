#pragma once
#include "game.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct GameReader GameReader;
struct GameReader
{
    Game* (*readGame)(char* inputFilePath);
    //TODO : Make structure for input Params and return them with this function temporary return void
    void (*readInputParams)(int, char**);
};

bool readScores(int* destination, int numOfPlayers, FILE* file);

bool readFields(Game* game, FILE* file);

//----------------------------------------------------------------------------

 Game* readGame(char* inputFilePath);


//reads input parameters    TODO : CHANGE RETURN VALUE
void readInputParams(int argc, char** argv);

//constructor
void initGameReader(GameReader* reader);

