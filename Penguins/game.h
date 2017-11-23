#pragma once
#include "player.h"
#include "field.h"

typedef enum GameStates GameStates;
enum GameStates { BEGINNING,
                  PLACEMENT,
                  GAME,
                  GAMEOVER};

typedef struct Dimension Dimension;
struct Dimension
{
    int row, col;
};

typedef struct Game Game;
struct Game
{
    //data
    Player* players;
    Field** board;
    Dimension boardDimension;
    GameStates state;
    //functions
    Field* (*getField)(int, int, Game*);
    Player* (*getPlayer)(int, Game*);
    void (*finalize)(Game*);
};

static Field** allocateMap(Dimension dimension)
{
    Field** retv;
    retv = (Field**) calloc(dimension.row, sizeof(Field*));
     if(retv == NULL)
        return NULL;
    int i;
    for(i = 0; i < dimension.row; ++i)
    {
        retv[i] = (Field*) calloc(dimension.col, sizeof(Field));
        if(retv[i] == NULL)
            return NULL;
    }

    return retv;
}

static bool isInProperRange(int row, int col, Game* game)
{
    return row <= game->boardDimension.row && row >= 0
            && col <= game->boardDimension.col && col >= 0;
}

static Field* getField(int row, int col, Game* game)
{
    if(!isInProperRange(row, col, game))
        exit(0);

    return (Field*)&game->board[row][col];
}

static Player* getPlayer(int playerId, Game* game)
{
    return (Player*)&game->players[playerId];
}

//freeing memory needs to be called at the end of game
static void finalize(Game* game)
{
    free(game->players);
    int i;
    for(i = 0; i < game->boardDimension.row; i++)
    {
        free(game->board[i]);
    }
    free(game->board);
    free(game);
}

static void assignFunctionsToPointers(Game* game)
{
    game->getField = &getField;
    game->getPlayer = &getPlayer;
    game->finalize = &finalize;
}

//function to create Game returns NULL when failed
static Game* createGame(int numberOfPlayers, Dimension boardDim)
{
    Game* retv = (Game*) malloc(sizeof(Game));
    if(retv == NULL)
        return NULL;

    retv->players = (Player*) calloc(numberOfPlayers, sizeof(Player));
    if(retv->players == NULL)
        return NULL;

    retv->board = allocateMap(boardDim);
    if(retv->board == NULL)
        return NULL;

    retv->boardDimension = boardDim;
    retv->state = BEGINNING;

    assignFunctionsToPointers(retv);

    return retv;
}
