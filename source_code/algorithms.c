#include "algorithms.h"


void placementPhase(Game* game)
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

bool checkFieldProperToMove(int x, int y, Game* game){
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

int checkMoveDirection(int x, int y, int endX, int endY){
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
        if(!(abs(differenceX)/2 == abs(differenceY))) // then its possible only when difX / 2 = +- difY
        return -1;
    }
    if(x%2 != endX%2){// if one is even and the other is odd
        //if(!((abs(differenceX))/2 == abs(differenceY)  || (abs(differenceX))/2 == abs(differenceY)))return -1;
        if(x%2 == 0){
            if(((distance + 1)/2) != differenceY && (1 - (distance + 1)/2) != differenceY )return -1;
        }else{
            if(((distance - 1)/2) != differenceY  && -(distance + 1)/2 != differenceY )return -1;

        }
    }
    if(x%2 == 0){
            if(differenceX > 0 && differenceY == 0)return 3;
            if(differenceX < 0 && differenceY == 0)return 5;

    }else{
            if(differenceX > 0 && differenceY == 0)return 2;
            if(differenceX < 0 && differenceY == 0)return 4;
    }

    if(differenceX > 0 && differenceY > 0)return 2;
    if(differenceX > 0 && differenceY < 0)return 3;
    if(differenceX < 0 && differenceY > 0)return 4;
    if(differenceX < 0 && differenceY < 0)return 5;

    return -1;
}

void colorFields(int x, int y, int Player, Game* game){
    int i=0, ii=0;
    for(i=0; i<game->boardDimension.row; i++){
        for(ii =0; ii<game->boardDimension.col; ii++){
            game->getField(i, ii, game)->POSSIBLEMOVECOLOR = true;
            if(isMovePossible(x, y, i, ii, Player, game)) game->getField(i, ii, game)->POSSIBLEMOVECOLOR = false;
        }
    }
}
void resetFieldColors(Game* game){
    int i=0, ii=0;
    for(i=0; i<game->boardDimension.row; i++){
        for(ii =0; ii<game->boardDimension.col; ii++){
            game->getField(i, ii, game)->POSSIBLEMOVECOLOR = false;
        }
    }
}

int isMovePossible(int x, int y, int endX, int endY, int Player, Game* game){
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
int checkStartPosition(int x, int y, int Player, Game* game){
    if(x < 0 || y < 0)return 1;
    if(x >= game->boardDimension.col)return 1;
    if(y >= game->boardDimension.row)return 1;
    if(!game->getField(x, y, game)->OCCUPIED_FLAG)return 2;
    if(!game->getField(x, y, game)->EXISTANCE_FLAG)return 2;
    if(game->getField(x, y, game)->playerID != Player)return 2;

    return 0;
}

void performMovement(int x, int y, int endX, int endY, Game* game){
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

int * choosePenguinAutomatically(int player, Game* game){
int Coords[2];
Coords[0] = -1;
Coords[1] = -1;

 int i=0, ii=0;
    for(i=0; i<game->boardDimension.row; i++){
        for(ii =0; ii<game->boardDimension.col; ii++){
           if(game->getField(i, ii, game)->OCCUPIED_FLAG){
                if(game->getField(i, ii, game)->playerID == player){
                    Coords[0] = i;
                    Coords[1] = ii;
                    return Coords;
                }
           }
        }
    }
    return Coords;
}

bool hasAvaibleMovement(Game* game, int Player){
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

void movementPhase(Game* game){
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
                printf("Player %d has no avaible movement.\nPress any key to continue.", i+1);
                getch();
                continue;
            }
            else isThereAnyMovement = true;

            int x = -1, y = -1, endX = -1, endY = -1;
            int movePossible = 0, startCoords = 0;
            do{
                printf("Turn of player %d.\n", i+1);

                do{
                if(game->numberOfPenguins > 1){
                printf("Choose start position [ROW : COLUMN] \n");
                scanf("%d %d", &x, &y);
                }else{
                    int *Coords = choosePenguinAutomatically(i, game);
                    x = Coords[0];
                    y = Coords[1];
                    printf("Start position has been chosen automatically to %d %d.\nPress any key to continue.", x, y);
                    getch();
                    continue;
                }

                startCoords = checkStartPosition(x, y, i, game);
                if(startCoords != 0){
                        fseek(stdin,0,SEEK_END);
                        SetConsoleTextAttribute(hConsole, FOREGROUND_RED);

                         switch(startCoords){
                            default : {break;}
                            case 1  : { printf("WRONG COORDINATES !\n");break;}
                            case 2  : { printf("INVALID START POSITION !\n");break;}
                        }
                }

                SetConsoleTextAttribute(hConsole, saved_attributes);


                }while(startCoords != 0);

                resetFieldColors(game);
                colorFields(x, y, i, game);
                writer.displayBoardOnConsol(game);

                printf("Choose end position [ROW : COLUMN] \n", i+1);
                scanf("%d %d", &endX, &endY);
                movePossible = isMovePossible(x, y, endX, endY, i, game);
                if(movePossible != 0){
                        resetFieldColors(game);
                        writer.displayBoardOnConsol(game);
                        fseek(stdin,0,SEEK_END);
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
            resetFieldColors(game);
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
