#include <stdio.h>
#include <stdlib.h>
#include "game_reader.h"
#include "algorithms.h"

int main(int argc, char** argv)
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
}
