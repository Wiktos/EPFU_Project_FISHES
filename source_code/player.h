#pragma once

typedef struct Player Player;
struct Player
{
    int score;
    int availablePenguins;
};

void initPlayer(int score, int availablePenguins, Player* player);
