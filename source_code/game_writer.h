#pragma once
#include "game.h"

#define ANSI_COLOR_GREEN    "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct GameWriter GameWriter;
struct GameWriter
{
    void (*write)(Game*, char*);
    void (*displayBoardOnConsol)(Game*);
};

static void write(Game* game, char* path)
{
    int i, j;
    FILE * fp;
    if(fp == NULL)
        goto ErrorHandler;
    fp = fopen(path, "w");

    //first row
    fprintf(fp, "%d ", game->numberOfPlayers);
    fprintf(fp, "%d ", game->getPlayer(0, game)->availablePenguins);
    fprintf(fp, "%d ", game->boardDimension.row);
    fprintf(fp, "%d\n", game->boardDimension.col);

    //second row
    for(i = 0; i < game->numberOfPlayers; i++)
    {
        fprintf(fp, "%d ", game->getPlayer(i, game)->score);
    }
    fprintf(fp, "\n");
    //board
    for(i = 0; i < game->boardDimension.row; i++)
    {
        for(j = 0; j < game->boardDimension.col; j++)
        {
            Field* currField = game->getField(i, j, game);
            if(currField->EXISTANCE_FLAG && !currField->OCCUPIED_FLAG)
                fprintf(fp, "%d ", currField->fishNumber);
            if(currField->EXISTANCE_FLAG && currField->OCCUPIED_FLAG)
                fprintf(fp, "%d ", -currField->playerID - 1);
            if(!currField->EXISTANCE_FLAG)
                fprintf(fp, "%d ", 0);
        }
        fprintf(fp, "\n");
    }

    return;

    ErrorHandler:
        exit(EXIT_FAILURE);
}

static void displayBoard(Game* game)
{
    int i,j;
    //works only in Windows enviroment
    system("cls");

    printf("Current scores : \n");
    for(i = 0; i < game->numberOfPlayers; i++)
    {
        Player* currPlayer = game->getPlayer(i, game);
        printf("Player %d : %d\n", i + 1, currPlayer->score);
    }

    printf("\n  ");
    for(i = 0; i < game->boardDimension.row; i++)
    {
        if(i % 2)
            printf(ANSI_COLOR_GREEN "_%d___" ANSI_COLOR_RESET, i);
        else
            printf(ANSI_COLOR_GREEN "%d__" ANSI_COLOR_RESET, i);
    }

    printf("  \n");

    for(i = 0; i < game->boardDimension.row; i++)
    {
        printf(ANSI_COLOR_GREEN "%d|" ANSI_COLOR_RESET, i);
        for(j = 0; j < game->boardDimension.col; j++)
        {

            if(i%2 == 0)
            {
                if(!game->getField(i,j,game)->EXISTANCE_FLAG)
                    printf("X   ");
                if(game->getField(i,j,game)->EXISTANCE_FLAG && !game->getField(i,j,game)->OCCUPIED_FLAG)
                    printf("%d   ",game->getField(i,j,game)->fishNumber);
                if(game->getField(i,j,game)->OCCUPIED_FLAG)
                {
                  printf("P%d  ",game->getField(i, j, game)->playerID + 1);
                }

            }
            else
            {
                if(!game->getField(i,j,game)->EXISTANCE_FLAG)
                    printf("  X ");
                if(game->getField(i,j,game)->EXISTANCE_FLAG && !game->getField(i,j,game)->OCCUPIED_FLAG)
                    printf("  %d ",game->getField(i,j,game)->fishNumber);
                if(game->getField(i,j,game)->OCCUPIED_FLAG)
                {
                  printf(" P%d ",game->getField(i,j,game)->playerID + 1);
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}

void initGameWriter(GameWriter* writer)
{
    writer->write = &write;
    writer->displayBoardOnConsol = &displayBoard;
}
