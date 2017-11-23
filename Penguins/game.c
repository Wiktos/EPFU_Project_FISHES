#pragma once
#include "player.c"
#include "field.c"

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
    Player* players;
    Field** board;
    Dimension boardDimension;
    GameStates state;
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

Game* createGame(int numberOfPlayers, Dimension boardDim)
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

    return retv;
}

void finalize(Game* game)
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
