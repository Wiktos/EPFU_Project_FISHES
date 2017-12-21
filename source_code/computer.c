#include "computer.h"
/*
    THE MC SAWYER WILL PRODUCE AI ALGORITHMS FOR PLACING AND MOVING PENGUIN
*/
void placement(Game* game, int player)
{
    printf("AI : PERFORMED PLACEMENT");
}

void movement(Game* game, int player)
{
    printf("AI : PERFORMED MOVEMENT");
}

void initComputer(Computer* computer)
{
    computer->placePenguin = &placement;
    computer->movePenguin = &movement;
}
