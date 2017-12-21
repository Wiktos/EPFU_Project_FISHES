#include <stdio.h>
#include <stdlib.h>
#include "game_reader.h"
#include "command_params.h"
#include "algorithms.h"
#include "computer.h"

//******* AUTOMATED MODE MAIN FUN ******************************

int main(int argc, char** argv)
{
    GameReader reader;
    initGameReader(&reader);

    CommandParams commandLineParams = reader.readInputParams(argc, argv);

    Game* game = reader.readGame(commandLineParams.inputPath);

    Computer AI;
    initComputer(&AI);
    /*
        AI STARTS TO DO JOB !
    */
    switch(commandLineParams.phase)
    {
        case MOVEMENT :
            AI.movePenguin(game, commandLineParams.player); break;
        case PLACEMENT :
            AI.placePenguin(game, commandLineParams.player); break;
        default :
            return -1;
    }

    GameWriter writer;
    initGameWriter(&writer);
    writer.write(game, commandLineParams.outputPath);

    finalizeGame(game);

    return 0;
}

//*****************************************************************


//******* INTERACTIVE MODE MAIN FUN ******************************

/*int main(int argc, char** argv)
{
    GameReader reader;
    initGameReader(&reader);
    reader.readInputParams(argc, argv);

    Game* game = reader.readGame("./resources/input.txt");

    Algorithms gamePhase;
    initAlgorithms(&gamePhase);

    game->state = PLACEMENT;
    gamePhase.placement(game);

    game->state = GAME;
    gamePhase.movement(game);

    GameWriter writer;
    initGameWriter(&writer);
    writer.write(game, "./resources/output.txt");

    finalizeGame(game);

    return 0;
}*/

//*****************************************************************
