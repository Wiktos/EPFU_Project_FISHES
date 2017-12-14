#include <stdio.h>
#include <stdlib.h>
#include "game_reader.h"
#include "algorithms.h"

int main(int argc, char** argv)
{
    GameReader reader;
    initGameReader(&reader);
    reader.readInputParams(argc, argv);

    Game* game = reader.readGame(".\\resources\\input.txt");

    Algorithms gamePhase;
    initAlgorithms(&gamePhase);

    game->state = PLACEMENT;
    gamePhase.placement(game);

    game->state = GAME;
    gamePhase.movement(game);

    /*
    //Phase 4 : Playing game
    while(game->state == GAME)
    {
        int i;
        for(i = 0; i < game->numberOfPlayers; ++i)
        {
            /*
                1. Check if current player has possible movement if no go to the next player [\/]
                2. Ask for movement [\/]
                3. Check if movement is possible if no ask again [\/]
                4. Update Game attributes and results [\/] (score, occupied, existence, etc. are changing in handleMovement())
                5. Notify Game.state if it needs to be changed -> change Game.state = GAMEOVER ( right now it only checks if there is any player who has movement, if not then gameover)
            */
	/*	game->state = GAMEOVER;
        }
    }*/
      /*
        Phase 5 : Game over
        1. Print results
    */
    GameWriter writer;
    initGameWriter(&writer);
    writer.write(game, "output.txt");

    finalizeGame(game);

    return 0;
}
