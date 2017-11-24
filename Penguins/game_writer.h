#pragma once
#include "game.h"

typedef struct GameWriter GameWriter;
struct GameWriter
{
    char* outputFilePath;
    void (*write)(Game*);
};

static void write(Game* game)
{
    //do writing
    return;
}

//constructor
GameWriter* createGameWriter(char* path)
{
    GameWriter* retv = (GameWriter*) malloc(sizeof(GameWriter));
    retv->outputFilePath = path;
    retv->write = &write;

    return retv;
}

//destructor
void finalizeGameWriter(GameWriter* writer)
{
    free(writer);
}
