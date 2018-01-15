#include "game_writer.h"
#include "algorithms.h"
#include <stdio.h>

void write(Game* game, char* path)
{
    int i, j;
    FILE * fp;
    fp = fopen(path, "w");
    if(fp == NULL)
        goto ErrorHandler;

    //first row
    fprintf(fp, "%d ", game->numberOfPlayers);
    fprintf(fp, "%d ", game->getPlayer(game->numberOfPlayers-1, game)->availablePenguins);
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

void displayBoard(Game* game)
{
    #ifdef _WIN32
    system("cls");
    #endif // _WIN32
    #ifdef __linux__
    system("clear");
    #endif // _WIN32

    int i,j;
    printf("Current scores : \n");
    for(i = 0; i < game->numberOfPlayers; i++)
    {
        Player* currPlayer = game->getPlayer(i, game);
        printf("Player %d : %d\n", i + 1, currPlayer->score);
    }

    if(game->state == MOVEMENT){
    printf("\n");
    printf("Players in game : \n");
    for(i = 0; i<game->numberOfPlayers; ++i){
            if(hasAvaibleMovement(game, i)){
                printf("PLAYER [ %d ] \n", i+1);
            }
        }
    }

    printf("\n  ");
    for(i = 0; i < game->boardDimension.row; i++)
    {
        if(i % 2)
        {
            char msg[16];
            sprintf(msg, "_%d___", i);
            PRINT(msg, GREEN);
        }
        else{
            char msg[16];
            sprintf(msg, "%d__", i);
            PRINT(msg, GREEN);
        }
    }

    printf("  \n");

    for(i = 0; i < game->boardDimension.row; i++)
    {
        if(i % 2){
            char msg[16];
            sprintf(msg, "| |\n|%d| ", i);
            PRINT(msg, GREEN);
        }
        else{
           char msg[16];
            sprintf(msg, "|%d| ", i);
            PRINT(msg, GREEN);
        }

        for(j = 0; j < game->boardDimension.col; j++)
        {
            if(i%2 == 0)
            {


                if(!game->getField(i,j,game)->EXISTANCE_FLAG){
                    PRINT("X   ", RED);
                }
                if(game->getField(i,j,game)->EXISTANCE_FLAG && !game->getField(i,j,game)->OCCUPIED_FLAG){
                    if(game->getField(i,j,game)->POSSIBLEMOVECOLOR){
                        char msg[16];
                        sprintf(msg, "%d   ",game->getField(i,j,game)->fishNumber);
                        PRINT(msg, BLUE);
                    }else{
                        printf("%d   ",game->getField(i,j,game)->fishNumber);
                    }

                }
                if(game->getField(i,j,game)->OCCUPIED_FLAG)
                {
                        char msg[16];
                        sprintf(msg, "P%d   ",game->getField(i,j,game)->playerID + 1);
                        PRINT(msg, YELLOW);
                }

            }
            else
            {
                if(!game->getField(i,j,game)->EXISTANCE_FLAG){
                    PRINT("X   ", RED);
                }
                if(game->getField(i,j,game)->EXISTANCE_FLAG && !game->getField(i,j,game)->OCCUPIED_FLAG){
                    if(game->getField(i,j,game)->POSSIBLEMOVECOLOR){
                        char msg[16];
                        sprintf(msg, "  %d ",game->getField(i,j,game)->fishNumber);
                        PRINT(msg, BLUE);
                    }else{
                        printf("  %d ",game->getField(i,j,game)->fishNumber);
                    }
                }
                if(game->getField(i,j,game)->OCCUPIED_FLAG)
                {
                        char msg[16];
                        sprintf(msg, " P%d ",game->getField(i,j,game)->playerID + 1);
                        PRINT(msg, YELLOW);
                }
            }
        }
        printf("\n");
        if(i % 2){
            PRINT("| |\n", GREEN);
        }

    }
    printf("\n");
}

void initGameWriter(GameWriter* writer)
{
    writer->write = &write;
    writer->displayBoardOnConsol = &displayBoard;
}
