#pragma once
#include "game.h"

typedef struct Computer Computer;
struct Computer
{
    void (*placePenguin)(Game*, int player);
    void (*movePenguin)(Game*, int player);
};

void initComputer(Computer* computer);
