#pragma once
#include "player.h"
#include "field.h"
#include "dimension.h"

typedef enum GameState GameState;
enum GameState { BEGINNING,
                  PLACEMENT,
                  MOVEMENT,
                  GAMEOVER};

typedef struct Game Game;
struct Game
{
    //data
    Player* players;
    int numberOfPlayers;
    int numberOfPenguins;
    Field** board;
    Dimension boardDimension;
    GameState state;
    //functions
    Field* (*getField)(int, int, Game*);
    Player* (*getPlayer)(int, Game*);
};

//constructor
Game* createGame(int numberOfPlayers, Dimension boardDim);

//destructor
void finalizeGame(Game* game);
