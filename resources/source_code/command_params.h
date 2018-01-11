#pragma once
#include <stdlib.h>

typedef struct CommandParams CommandParams;
struct CommandParams
{
    char* inputPath;
    char* outputPath;
    GameState phase;
    int player;
};

