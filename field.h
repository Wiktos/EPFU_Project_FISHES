#pragma once
#include <stdbool.h>
#include <math.h>

typedef struct Field Field;
struct Field
{
    int fishNumber;
    int playerID;
    bool OCCUPIED_FLAG;
    bool EXISTANCE_FLAG;
};

void initField(int fishNumber, Field* field)
{
    if(fishNumber < 0)
    {
        field->OCCUPIED_FLAG = true;
        field->playerID = fabs(fishNumber);
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
