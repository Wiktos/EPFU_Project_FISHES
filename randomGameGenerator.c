#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>


bool placementChecker(int row, int col, int field[row][col], int penguins){
    int sum, i, ii;
    sum = 0;
    for(i = 0; i < row; i++){
        for(ii = 0; ii < col; ii++){
            if(field[i][ii] == 1){
                sum++;
            }
        }
    }
    return (sum >= penguins);
}


int main()
{
    int players, seed, penguins, i, ii;
    time_t tt;
    seed = time(&tt);
    srand(seed);
    players = 2 + rand() % 5;
    FILE * fp;
    fp = fopen("input.txt", "w");
    fprintf(fp, "%d ", players);
    penguins = players + (rand() % 5) * players;
    fprintf(fp, "%d ", penguins);
    int columns, rows;
    columns = rand() % 11;
    rows = rand() % 11;
    while(columns * rows < penguins){
        columns += 2;
        rows += 2;
    }
    fprintf(fp, "%d ", rows);
    fprintf(fp, "%d\n", columns);
    for(i = 0; i < players; i++){
        fprintf(fp, "0 ");
    }
    fprintf(fp, "\n");
    //creating 2d array with fields//
    int field[rows][columns];
    for(i = 0; i < rows; i++){
        for(ii = 0; ii < columns; ii++){
            field[i][ii] = rand() % 4;
        }
    }
    //checking if placement is possible//
    while(placementChecker(rows, columns, field, penguins) == false){
        for(i = 0; i < rows; i++){
            for(ii = 0; ii < columns; ii++){
                field[i][ii] = rand() % 4;
            }
        }
    }

    for(i = 0; i < rows; i++){
        for(ii = 0; ii< columns; ii++){
            fprintf(fp, "%d ", field[i][ii]);
        }
        fprintf(fp, "\n");
    }
    return 0;
}

