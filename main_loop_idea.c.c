#include <stdio.h>

int main()
{
    /*  Phase 1 : Program params
        1. Read program params
        2. Check correctness of params
    */

    /*  Phase 2 : Input file
        while(Input file not empty)
        {
            1. Read data from input file
            2. Check correctness of current readed data if failed then stop program
            3. Assign data to Game structure
        }
    */

    // Set Game.state == PLACEMENT

    //Phase 3 :  Placement penguin
    while(Game.state == PLACEMENT)
    {
        for(int i = 0; i < Game.numberOfPlayers; ++i)
        {
            /*
                1. Player choose field for his penguin
                2. Check correctness of this move if failed ask again for move
                3. Notify Game.state if it needs to be changed -> change Game.state = GAME
            */
        }
    }

    //Phase 4 : Playing game
    while(Game.state == GAME)
    {
        for(int i = 0; i < Game.numberOfPlayers; ++i)
        {
            /*
                1. Check if current player has possible movement if no go to the next player
                2. Ask for movement
                3. Check if movement is possible if no ask again
                4. Update Game attributes and results
                5. Notify Game.state if it needs to be changed -> change Game.state = GAMEOVER
            */
        }
    }

    /*
        Phase 5 : Game over
        1. Print results
    */

    return 0;
}
