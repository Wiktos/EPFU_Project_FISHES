#pragma once

typedef struct Player Player;
struct Player
{
    int score;
    int availablePlayers;
};

void initPlayer(int score, int availablePenguins, Player* field)
{
    field->score = score;
    field->availablePenguins = availablePenguins;
}
