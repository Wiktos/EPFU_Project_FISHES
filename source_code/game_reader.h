#pragma once
#include "game.h"
#include "command_params.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct GameReader GameReader;
struct GameReader
{
    Game* (*readGame)(char* inputFilePath);
    CommandParams (*readInputParams)(int, char**);
};

bool readScores(int* destination, int numOfPlayers, FILE* file);

bool readFields(Game* game, FILE* file);

//----------------------------------------------------------------------------

Game* readGame(char* inputFilePath);

CommandParams readInputParams(int argc, char** argv);

//constructor
void initGameReader(GameReader* reader);

