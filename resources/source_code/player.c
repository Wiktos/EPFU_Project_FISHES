#include "player.h"

void initPlayer(int score, int availablePenguins, Player* player)
{
    player->score = score;
    player->availablePenguins = availablePenguins;
}

