#include "game_writer.h"
#include <stdio.h>

void write(Game* game, char* path)
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

void displayBoard(Game* game)
{
    system("cls");
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    int i,j;
    //works only in Windows enviroment


    printf("Current scores : \n");
    for(i = 0; i < game->numberOfPlayers; i++)
    {
        Player* currPlayer = game->getPlayer(i, game);
        printf("Player %d : %d\n", i + 1, currPlayer->score);
    }

    printf("\n  ");
    for(i = 0; i < game->boardDimension.row; i++)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        if(i % 2)
            printf("_%d___", i);
        else
            printf("%d__", i);
        SetConsoleTextAttribute(hConsole, saved_attributes);
    }

    printf("  \n");

    for(i = 0; i < game->boardDimension.row; i++)
    {
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        if(i % 2)
            printf("| |\n|%d| ", i);
        else
            printf("|%d| ", i);

        SetConsoleTextAttribute(hConsole, saved_attributes);
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
                  printf("P%d  ",game->getField(i,j, game)->playerID + 1);
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
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        if(i % 2)printf("| |\n");
        SetConsoleTextAttribute(hConsole, saved_attributes);

    }
    printf("\n");
}

void initGameWriter(GameWriter* writer)
{
    writer->write = &write;
    writer->displayBoardOnConsol = &displayBoard;
}
