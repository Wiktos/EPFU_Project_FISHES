#pragma once
#include "game_writer.h"
#include "placement.h"
#include <stdio.h>

typedef struct Algorithms Algorithms;
struct Algorithms
{
    void (*placement)(Game*);
    void (*movement)(Game*);
};
enum COLOR{
    DEFAULT,
    RED,
    GREEN,
    BLUE,
    YELLOW
};
