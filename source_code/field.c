#include "field.h"

void initField(int fishNumber, Field* field)
{
    field->POSSIBLEMOVECOLOR = false;
    if(fishNumber < 0)
    {
        field->OCCUPIED_FLAG = true;
        field->playerID = fabs(fishNumber) - 1;
    }
    else
    {
        field->OCCUPIED_FLAG = false;
        field->fishNumber = fishNumber;
    }
    if(fishNumber == 0)
        field->EXISTANCE_FLAG = false;
    else
        field->EXISTANCE_FLAG = true;
}
