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

void initField(int fishNumber, Field* field);
