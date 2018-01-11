#pragma once
#include "game.h"
#include "windows.h"

typedef struct GameWriter GameWriter;
struct GameWriter
{
    void (*write)(Game*, char*);
    void (*displayBoardOnConsol)(Game*);
};

void initGameWriter(GameWriter* writer);
