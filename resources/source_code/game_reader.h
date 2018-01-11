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

void initGameReader(GameReader* reader);

