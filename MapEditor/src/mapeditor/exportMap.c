#include "exportMap.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void exportMap(Tile *tileArr) {
    FILE *file = fopen("../Game/assets/map.mp", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    for (int i = 0; i < MAXTILES; i++) {
        fprintf(file, "%d{%d,%d,%d}", 
            tileArr[i].id, 
            tileArr[i].walkable, 
            tileArr[i].weaponBuy, 
            tileArr[i].perkBuy
        );
        if (i < MAXTILES - 1) {
            fprintf(file, ";");
        }
    }
    fclose(file);
}


