#pragma once
#include "game_writer.h"
#include "placement.h"
#include <stdio.h>

typedef struct Algorithms Algorithms;
struct Algorithms
{
    void (*placement)(Game*);
    void (*movement)(Game*);
};

static void placementPhase(Game* game)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

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

                    printf("Player %d give coordinates, [ROW : COLUMN] for placing a penguin: ", j + 1);
                    scanf("%d %d",&x,&y);

                    if(isChosenFieldCorrect(x, y, game))  //if coordinates are correct assign a player for a field
                    {
                          placeOnField(x, y, j, game);
                          break;
                    }
                    else
                    {
                        fseek(stdin,0,SEEK_END);
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                        printf("WRONG COORDINATES !\n");
                        SetConsoleTextAttribute(hConsole, saved_attributes);
                    }
                  }
            }
        }
        writer.displayBoardOnConsol(game);
        break;
    }
}

static bool checkFieldProperToMove(int x, int y, Game* game){
    if(x < 0 || y < 0)return false;
    if(x >= game->boardDimension.col)return false;
    if(y >= game->boardDimension.row)return false;
    if(!game->getField(x, y, game)->EXISTANCE_FLAG) return false;
    if(game->getField(x, y, game)->OCCUPIED_FLAG) return false;
return true;
}

bool checkingMovementRecursive(int x, int y, int endX, int endY, int movementDirection, Game* game){
    if(x == endX && y == endY)return true;
    if(x%2 == 0){
                switch(movementDirection){
                    default :{return false;}
                    //left
                    case 0:{y--; break;}
                    // right
                    case 1:{y++; break;}
                    //// up left
                    case 2:{x--; y--;break;}
                    //up right
                    case 3:{x--; break;}
                    //down left
                    case 4:{x++; y--;break;}
                    //down right
                    case 5:{x++; break;}
                }
            }else{
               switch(movementDirection){
                    default :{return false;}
                    //left
                    case 0:{y--; break;}
                    //right
                    case 1:{y++; break;}
                    //up left
                    case 2:{x--; break;}
                    //up right
                    case 3:{x--; y++; break;}
                    //down left
                    case 4:{x++; break;}
                    //down right
                    case 5:{x++; y++; break;}
                }
            }
        if(!checkFieldProperToMove(x, y, game))return false;
        else return checkingMovementRecursive(x, y, endX, endY, movementDirection, game);
}

static int checkMoveDirection(int x, int y, int endX, int endY){
    // return values
    // 0 - left
    // 1 - right
    // 2 - up left
    // 3 - up right
    // 4 - down left
    // 5 - down right
    int differenceX = x - endX;
    int differenceY = y - endY;
    int distance = abs(differenceX);

    if(abs(differenceX) > 1 && differenceY == 0)return -1;
    if(differenceX == 0){
        if(differenceY > 0)return 0;
        if(differenceY < 0)return 1;
    }

    if(x%2 == endX%2){
        if(!abs(differenceX)/2 == abs(differenceY)) // then its possible only when difX / 2 = +- difY
        return -1;
    }
    if(x%2 != endX%2){// if one is even and the other is odd
        if(!abs(differenceX + 1)/2 == abs(differenceY))return -1;
    }
    if(differenceX > 0 && differenceY > 0)return 2;
    if(differenceX > 0 && differenceY < 0)return 3;
    if(differenceX < 0 && differenceY > 0)return 4;
    if(differenceX < 0 && differenceY < 0)return 5;

    return -1;
}

static int isMovePossible(int x, int y, int endX, int endY, int Player, Game* game){
    if(x < 0 || y < 0 || endX < 0 || endY < 0)return 1;
    if(x >= game->boardDimension.col)return 1;
    if(y >= game->boardDimension.row)return 1;
    if(endX >= game->boardDimension.col)return 1;
    if(endY >= game->boardDimension.row)return 1;
    if(!game->getField(x, y, game)->OCCUPIED_FLAG)return 2;
    if(!game->getField(x, y, game)->EXISTANCE_FLAG)return 2;
    if(game->getField(x, y, game)->playerID != Player)return 2;
    if(game->getField(endX, endY, game)->OCCUPIED_FLAG)return 3;
    if(!game->getField(endX, endY, game)->EXISTANCE_FLAG)return 3;
    if(x == endX && y == endY)return 4;

    int moveDirection = checkMoveDirection(x, y, endX, endY);
    if(moveDirection == -1)return 4;
    if(!checkingMovementRecursive(x, y, endX, endY, moveDirection, game))return 4;

    return 0;
}
static void performMovement(int x, int y, int endX, int endY, Game* game){
    int Player =  game->getField(x, y, game)->playerID;

    game->getField(x, y, game)->EXISTANCE_FLAG = false;
    game->getField(x, y, game)->OCCUPIED_FLAG = false;
    game->getField(x, y, game)->playerID = 0;
    game->getField(x, y, game)->fishNumber = 0;

    game->getField(endX, endY, game)->OCCUPIED_FLAG = true;
    game->getField(endX, endY, game)->playerID = Player;
    game->getPlayer(Player, game)->score += game->getField(endX, endY, game)->fishNumber;
    game->getField(endX, endY, game)->fishNumber = 0;

}



static bool hasAvaibleMovement(Game* game, int Player){
    int i, ii;
    for(i=0; i<game->boardDimension.row; ++i){
        for(ii=0; ii<game->boardDimension.col; ++ii){
            if(!game->getField(i, ii, game)->OCCUPIED_FLAG)continue;
            if(game->getField(i, ii, game)->playerID != Player)continue;
            //check move left
            if(checkFieldProperToMove(i, ii - 1, game))return true;
            //check move right
            if(checkFieldProperToMove(i, ii + 1, game))return true;

            if(i%2 == 0){
                //check move up left
                if(checkFieldProperToMove(i-1, ii-1, game))return true;
                //check move up right
                if(checkFieldProperToMove(i-1, ii, game))return true;
                //check move down left
                if(checkFieldProperToMove(i+1, ii-1, game))return true;
                //check move down right
                if(checkFieldProperToMove(i+1, ii, game))return true;
            }else{
                //check move up left
                if(checkFieldProperToMove(i-1, ii, game))return true;
                //check move up right
                if(checkFieldProperToMove(i-1, ii+1, game))return true;
                //check move down left
                if(checkFieldProperToMove(i+1, ii, game))return true;
                //check move down right
                if(checkFieldProperToMove(i+1, ii+1, game))return true;
            }
        }
    }
    return false;
}

static void movementPhase(Game* game){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    WORD saved_attributes;

    /* Save current attributes */
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    saved_attributes = consoleInfo.wAttributes;

    GameWriter writer;
    initGameWriter(&writer);
    writer.displayBoardOnConsol(game);

    bool isThereAnyMovement = false;
    int i=0;
    while(game->state == GAME)
    {
        isThereAnyMovement = false;

        for(i=0; i<game->numberOfPlayers; ++i){
            writer.displayBoardOnConsol(game);
            if(!hasAvaibleMovement(game, i)){
                printf("Player %d has no avaible movement. \n Press any key to continue.", i+1);
                getch();
                continue;
            }
            else isThereAnyMovement = true;

            int x = -1, y = -1, endX = -1, endY = -1;
            int movePossible = 0;
            do{
                if(movePossible == 0)printf("Turn of player %d.\nChoose start position [ROW : COLUMN] and end position [ROW : COLUMN] \n", i+1);
                scanf("%d %d %d %d", &x, &y, &endX, &endY);
                movePossible = isMovePossible(x, y, endX, endY, i, game);

                if(movePossible != 0){
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

                         switch(movePossible){
                            default : {break;}
                            case 1  : { printf("WRONG COORDINATES !\n");break;}
                            case 2  : { printf("INVALID START POSITION !\n");break;}
                            case 3  : { printf("INVALID DESTINATION !\n");break;}
                            case 4  : { printf("INVALID MOVEMENT !\n");break;}
                        }

                        SetConsoleTextAttribute(hConsole, saved_attributes);
                }
            }while(movePossible != 0);

            performMovement(x, y, endX, endY, game);
            writer.displayBoardOnConsol(game);
        }

        if(!isThereAnyMovement)game->state = GAMEOVER;
    }
}

void initAlgorithms(Algorithms* algo)
{
    algo->placement = &placementPhase;
    algo->movement = &movementPhase;
}
