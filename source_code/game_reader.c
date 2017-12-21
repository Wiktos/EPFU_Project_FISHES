#include "game_reader.h"

//reads game from input file function
bool checkNumberOfPlayers(int);
bool checkNumberOfPenguins(int, int);
bool checkDimmension(int);
bool checkScoreOfPlayer(int, int);
bool checkFieldProperty(int, int);

bool readScores(int* destination, int numOfPlayers, FILE* file)
{
    int i, sumOfScore = 0;
    for(i = 0; i < numOfPlayers; i++)
    {
        if (fscanf(file, "%d", &destination[i]) != 1)
            return false;

        sumOfScore += destination[i];

        if(checkScoreOfPlayer(destination[i], sumOfScore) == false)
            return false;
    }

    return true;
}

bool readFields(Game* game, FILE* file)
{
    int i, j, currField = game->numberOfPlayers + 1; // +1 because we don't expect that value in input file so every validation function will return false
    Dimension boardDim = game->boardDimension;

	for(i = 0; i < boardDim.row; i++)
	{
           for(j = 0; j < boardDim.col; j++)
            {
                int result = fscanf(file, "%d", &currField);
                if(result != EOF && result != 0 && checkFieldProperty(currField, game->numberOfPlayers))
                {
                    initField(currField, game->getField(i, j, game));
                }
                else
                    return false;
            }
    }
    return true;
}

//----------------------------------------------------------------------------

Game* readGame(char* inputFilePath)
{
    int numberOfPlayers, availablePenguins;
    int i;
    Dimension boardDim;

    FILE * filePointer;
    filePointer = fopen(inputFilePath, "r");

    //1. Read first row from input file to the variables above
    if (fscanf(filePointer, "%d", &numberOfPlayers) != 1 || !checkNumberOfPlayers(numberOfPlayers))
        goto ErrorHandler;

    if (fscanf(filePointer, "%d", &availablePenguins) != 1)
        goto ErrorHandler;

    if (fscanf(filePointer, "%d", &boardDim.row) != 1 || checkDimmension(boardDim.row) == false)
        goto ErrorHandler;

    if (fscanf(filePointer, "%d", &boardDim.col) != 1 || checkDimmension(boardDim.col) == false)
        goto ErrorHandler;

    Game* retGame = createGame(numberOfPlayers, boardDim);
    if(retGame == NULL)
        goto ErrorHandler;

    if(checkNumberOfPenguins(availablePenguins, boardDim.col * boardDim.row) == false)
        goto ErrorHandler;

    int* scores = (int*) calloc(numberOfPlayers, sizeof(int));

    //2. Read scores for every player to scores table
    bool result = readScores(scores, numberOfPlayers, filePointer);
    if(!result)
        goto ErrorHandler;

    for(i = 0; i < numberOfPlayers; i++)
    {
        initPlayer(scores[i], availablePenguins, retGame->getPlayer(i, retGame));
    }

    retGame->numberOfPenguins = availablePenguins;
    //3. Read and initialize every field
    result = readFields(retGame, filePointer);
    if(!result)
        goto ErrorHandler;

    fclose(filePointer);

    return retGame;

ErrorHandler :
    perror("Error while reading game from input file");
    exit(EXIT_FAILURE);
}


//reads input parameters    TODO : CHANGE RETURN VALUE
void readInputParams(int argc, char** argv)
{
    //do reading
    return /*PARAMS STRUCTURE*/;
}

//constructor
void initGameReader(GameReader* reader)
{
    reader->readGame = &readGame;
    reader->readInputParams = &readInputParams;
}

bool checkNumberOfPlayers(int n)
{
	return n >= 2;
}

bool checkNumberOfPenguins(int numOfPenguins, int numOfFields)
{
	return numOfPenguins <= numOfFields;
}

bool checkDimmension(int n)
{
    return n >= 2;
}

bool checkScoreOfPlayer(int score, int sum)
{
	return !((score<0)||(score>sum));
}

bool checkFieldProperty(int field, int n)
{
	return !((field > 3 )||(field < (-1) * n));
}


