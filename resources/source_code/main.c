#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_reader.h"
#include "command_params.h"
#include "algorithms.h"
#include "computer.h"

//******* AUTOMATED MODE MAIN FUN ******************************

int main(int argc, char** argv)
{
    srand(time(NULL));
    GameReader reader;
    initGameReader(&reader);

    CommandParams commandLineParams = reader.readInputParams(argc, argv);

    Game* game = reader.readGame(commandLineParams.inputPath);

    if(commandLineParams.player + 1 > game->numberOfPlayers)
    {
        printf("Command line parameter : Wrong player number\n");
        return -1;
    }

    Computer AI;
    initComputer(&AI);
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
/*
int main(int argc, char** argv)
{
    GameReader reader;
    initGameReader(&reader);

    Game* game = reader.readGame("./resources/input.txt");

    Algorithms gamePhase;
    initAlgorithms(&gamePhase);

    game->state = PLACEMENT;
    gamePhase.placement(game);

    game->state = MOVEMENT;
    gamePhase.movement(game);

    GameWriter writer;
    initGameWriter(&writer);
    writer.write(game, "./resources/output.txt");

    finalizeGame(game);

    return 0;
}
*/
//*****************************************************************
