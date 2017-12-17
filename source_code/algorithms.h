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

void    placementPhase(Game* game);
bool    checkFieldProperToMove(int x, int y, Game* game);
bool    checkingMovementRecursive(int x, int y, int endX, int endY, int movementDirection, Game* game);
int     checkMoveDirection(int x, int y, int endX, int endY);
int     isMovePossible(int x, int y, int endX, int endY, int Player, Game* game);
void    performMovement(int x, int y, int endX, int endY, Game* game);
bool    hasAvaibleMovement(Game* game, int Player);
void    movementPhase(Game* game);
void    initAlgorithms(Algorithms* algo);
