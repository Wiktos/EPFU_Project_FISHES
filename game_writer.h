#pragma once
#include "game.h"
#include "windows.h"

typedef struct GameWriter GameWriter;
struct GameWriter
{
    void (*write)(Game*, char*);
    void (*displayBoardOnConsol)(Game*);
};

void write(Game* game, char* path);

void displayBoard(Game* game);

void initGameWriter(GameWriter* writer);
