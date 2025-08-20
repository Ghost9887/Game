#include "exportMap.h"
#include <stdio.h>
#include <stdlib.h>

void exportMap(int *arr) {
    FILE *file = fopen("../Game/assets/map.mp", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    for (int i = 0; i < MAXTILES; i++) {
        fprintf(file, "%d", arr[i]);
        if (i < MAXTILES - 1) {
            fprintf(file, ",");
        }
    }
    fclose(file);
}


int *parseMap(Tile *tileArr) {
    int *arr = malloc(sizeof(int) * MAXTILES);
    if (arr == NULL) {
        return NULL;
    }
    int size = 32;
    int tilesPerRow = 7000 / size;
    int tilesPerColumn = 7000 / size;
    int index = 0;
    for (int y = 0; y < tilesPerColumn; y++) {
        for (int x = 0; x < tilesPerRow; x++) {
            arr[index] = tileArr[index].id;
            index++;
        }
    }
    return arr;
}

