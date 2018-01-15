#include "computer.h"
#include "algorithms.h"
/*
    THE MC SAWYER WILL PRODUCE AI ALGORITHMS FOR PLACING AND MOVING PENGUIN
*/
void placement(Game* game, int player)
{
    printf("AI : PERFORMED PLACEMENT\n");
    bool FieldGood = false;
    do{
        if(!checkIfExistAnyField(game)){
                 printf("There is no available field for placement.\n");
                break;
        }
        int x = rand()%game->boardDimension.row;
        int y = rand()%game->boardDimension.col;
        if(isChosenFieldCorrect(x, y, game)){placeOnField(x, y, player, game);FieldGood = true; printf("PLACEMENT ON: %d %d \n", x, y);}

    }while(!FieldGood);
}

void movement(Game* game, int player)
{
    printf("AI : PERFORMED MOVEMENT\n");

        bool FieldGood = false;
    do{
            if(!hasAvaibleMovement(game, player)){
                 printf("There is no available field for movement.\n");
                break;
        }


        int x = rand()%game->boardDimension.row;
        int y = rand()%game->boardDimension.col;

        int endX = rand()%game->boardDimension.row;
        int endY = rand()%game->boardDimension.col;

        if(isMovePossible(x, y, endX, endY, player, game) == 0){
            performMovement(x, y, endX, endY, game);
            printf("MOVEMENT ON: %d %d %d %d", x, y, endX, endY);
            FieldGood = true;
        }

    }while(!FieldGood);
}

void initComputer(Computer* computer)
{
    computer->placePenguin = &placement;
    computer->movePenguin = &movement;
}
