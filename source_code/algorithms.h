#pragma once
#include "game_writer.h"
#include "placement.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef struct Algorithms Algorithms;
struct Algorithms
{
    void (*placement)(Game*);
    void (*movement)(Game*);
};

static void placementPhase(Game* game)
{
    while(game->state == PLACEMENT)
    {
        GameWriter writer;
        initGameWriter(&writer);
        int x, y, j;

        if(!checkIfExistAnyField(game))
            break;

        writer.displayBoardOnConsol(game);

        while(game->getPlayer(0 , game)->availablePenguins != 0)
        {
            for(j = 0; j < game->numberOfPlayers; j++)
            {
               writer.displayBoardOnConsol(game);

                  while(1)    //Do it until field is correct
                  {

                    printf("Player %d give coordinates x y for placing a penguin: ", j + 1);
                    scanf("%d %d",&x,&y);

                    if(isChosenFieldCorrect(x,y,game))  //if coordinates are correct assign a player for a field
                    {
                          placeOnField(x, y, j, game);
                          break;
                    }
                    else
                    {
                        fseek(stdin,0,SEEK_END);
                        printf(ANSI_COLOR_RED "WRONG COORDINATES !\n" ANSI_COLOR_RESET);
                    }
                  }
            }
        }
        writer.displayBoardOnConsol(game);
        break;
    }
}

void initAlgorithms(Algorithms* algo)
{
    algo->placement = &placementPhase;
}
