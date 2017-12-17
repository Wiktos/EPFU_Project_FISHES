#include "dimension.h"
Dimension* createDimension(int row, int col)
{
    Dimension* retv = (Dimension*) malloc(sizeof(Dimension));
    retv->row = row;
    retv->col = col;

    return retv;
}

void finalizeDimension(Dimension* dim)
{
    free(dim);
}
