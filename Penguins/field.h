#pragma once
#include <stdbool.h>

typedef struct Field Field;
struct Field
{
    int fishNumber;
    bool OCCUPIED_FLAG;
    bool EXISTANCE_FLAG;
};

void initField(int fishNumber, Field* field)
{
    field->fishNumber = fishNumber;
    if(fishNumber < 0)
        field->OCCUPIED_FLAG = true;
    if(fishNumber == 0)
        field->EXISTANCE_FLAG = true;
}
