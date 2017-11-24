    int numberOfPlayers, numberOfPenguins, numberOfRows, numberOfColumns,i;
    int score[30];
    FILE * filePointer;
    filePointer=fopen("input_file.txt", "r");
    if (fscanf(filePointer,"%d",&numberOfPlayers)!=1)
        return 0;
    if (fscanf(filePointer,"%d",&numberOfPenguins)!=1)
        return 0;
    if (fscanf(filePointer,"%d",&numberOfRows)!=1)
        return 0;
    if (fscanf(filePointer,"%d",&numberOfColumns)!=1)
        return 0;
    int x = feof(filePointer) ? EOF : 0;
    while (x != EOF && x != '\n') x = fgetc(filePointer);     //this moves the pointer to new line//
    for(i=0;i<numberOfPlayers;i++)
        if (fscanf(filePointer,"%d",&score[i])!=1)
            return 0;
    int field[numberOfRows][numberOfColumns];