#include <stdio.h>
#include <stdlib.h>
#include "game_reader.h"
#include "game_writer.h"

int main(int argc, char** argv)
{
    /*  Phase 1 : Program params
        1. Read program params
        2. Check correctness of params
    */
    GameReader* reader = createGameReader("path_to_input_file");
    reader ->readInputParams(argc, argv);

    /*  Phase 2 : Input file
        while(Input file not empty)
        {
            1. Read data from input file
            2. Check correctness of current readed data if failed then stop program
            3. Assign data to Game structure
        }
    */
    Game* game = reader->readGame();
    finalizeGameReader(reader);

    game->state = PLACEMENT;
    //Phase 3 :  Placement penguin
    while(game->state == PLACEMENT)
    {
        int i;
        for(i = 0; i < game->numberOfPlayers; ++i)
        {
            /*
                1. Player choose field for his penguin
                2. Check correctness of this move if failed ask again for move
                3. Notify Game.state if it needs to be changed -> change Game.state = GAME
            */
        }
        game->state = GAME;
    }

    //Phase 4 : Playing game
    while(game->state == GAME)
    {
        int i;
        for(i = 0; i < game->numberOfPlayers; ++i)
        {
            /*
                1. Check if current player has possible movement if no go to the next player
                2. Ask for movement
                3. Check if movement is possible if no ask again
                4. Update Game attributes and results
                5. Notify Game.state if it needs to be changed -> change Game.state = GAMEOVER
            */
        }
        game->state = GAMEOVER;
    }

      /*
        Phase 5 : Game over
        1. Print results
    */
    GameWriter* writer = createGameWriter("path_to_output_file");
    writer->write(game);
    finalizeGameWriter(writer);

    /*
        Phase 6 : Deallocating memory of game
    */
    //int i; scanf("%d", &i);   can be deleted just to see if memory is deallocated properly
    finalizeGame(game);
    //int j; scanf("%d", &j);    can be deleted just to see if memory is deallocated properly

    return 0;
}
