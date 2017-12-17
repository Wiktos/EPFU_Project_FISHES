#pragma once

typedef struct Dimension Dimension;
struct Dimension
{
    int row, col;
};

Dimension*  createDimension(int row, int col);
void        finalizeDimension(Dimension* dim);
