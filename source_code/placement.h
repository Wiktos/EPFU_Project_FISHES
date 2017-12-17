#pragma once
#include "game.h"

bool checkIfExistAnyField(Game* game);

bool isChosenFieldCorrect(int x, int y, Game* game);

void placeOnField(int x, int y, int playerID, Game* game);
