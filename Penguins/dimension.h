#pragma once

typedef struct Dimension Dimension;
struct Dimension
{
    int row, col;
};

Dimension* createDimension(int row, int col)
{
    Dimension retv;
    retv.row = row;
    retv.col = col;
    return (Dimension*)&retv;
}
