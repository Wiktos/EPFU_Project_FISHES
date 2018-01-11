#include "placement.h"

bool checkIfExistAnyField(Game* game)
{
	int i, j;
	for (i = 0; i<game->boardDimension.row; i++)
	{
		for (j = 0; j < game->boardDimension.col; j++)
		{
		    Field* currField = game->getField(i, j, game);
			if (currField->EXISTANCE_FLAG == true && currField->OCCUPIED_FLAG == false)
                return true;
		}
    }
    return false;
}

bool isChosenFieldCorrect(int x, int y, Game* game)
{
	return (isInProperRange(x,y,game) && game->getField(x, y, game)->EXISTANCE_FLAG
         && !game->getField(x, y, game)->OCCUPIED_FLAG && game->getField(x,y, game)->fishNumber <= 1);
}

void placeOnField(int x, int y, int playerID, Game* game)
{
			game->getField(x, y, game)->playerID = playerID;
			game->getPlayer(playerID, game)->availablePenguins--;
			game->getPlayer(playerID, game)->score++;
			game->getField(x,y,game)->fishNumber = 0;
			game->getField(x,y,game)->OCCUPIED_FLAG=true;
}

