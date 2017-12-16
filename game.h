#pragma once
#include "player.h"
#include "field.h"
#include "dimension.h"

typedef enum GameStates GameStates;
enum GameStates { BEGINNING,
                  PLACEMENT,
                  GAME,
                  GAMEOVER};

typedef struct Game Game;
struct Game
{
    //data
    Player* players;
    int numberOfPlayers;
    Field** board;
    Dimension boardDimension;
    GameStates state;
    //functions
    Field* (*getField)(int, int, Game*);
    Player* (*getPlayer)(int, Game*);
};

Field** allocateMap(Dimension dimension);

bool isInProperRange(int row, int col, Game* game);

Field* getField(int row, int col, Game* game);

Player* getPlayer(int playerId, Game* game);

void assignFunctionsToPointers(Game* game);

//constructor
Game* createGame(int numberOfPlayers, Dimension boardDim);

//destructor
void finalizeGame(Game* game);
