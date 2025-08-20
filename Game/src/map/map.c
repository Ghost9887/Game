#include "map.h"
#include "tile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void loadMap(int *mapArr){
   FILE *file = fopen("assets/map.mp", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    char buffer[100000]; 
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Failed to read file");
        fclose(file);
        return;
    }
    fclose(file);
    char *comma = strtok(buffer, ",");
    int index = 0;
    while (comma != NULL && index < MAXTILES) {
        mapArr[index] = atoi(comma);
        comma = strtok(NULL, ",");
        index++;
    } 
    printf("Map Loaded Successfully\n");
}

void drawMap(Tile *tileArr, Texture2D *tileTexturesArr){
  for (int i = 0; i < MAXTILES; i++) {
    if(tileArr[i].active){
      Vector2 pos = {tileArr[i].x, tileArr[i].y};
      Rectangle rec = {0, 0, tileArr[i].width, tileArr[i].height }; //size of tile
      DrawTextureRec(tileTexturesArr[tileArr[i].id], rec, pos, WHITE);
    }
  }
}


void initTileArr(Tile *tileArr, int *mapArr) {
    int size = 32;
    int tilesPerRow = 7104 / size;
    int tilesPerColumn = 7104 / size;
    int index = 0;
    for (int y = 0; y < tilesPerColumn; y++) {
        for (int x = 0; x < tilesPerRow; x++) {
            tileArr[index].x = x * size;
            tileArr[index].y = y * size;
            tileArr[index].width = 32;
            tileArr[index].height = 32;
            tileArr[index].active = true;
            tileArr[index].walkable = false;
            tileArr[index].id = mapArr[index];
            index++;
        }
    }
}

void loadTileTextures(Texture2D *tileTexturesArr){
  tileTexturesArr[0] = LoadTexture("assets/tiles/white.png");
  tileTexturesArr[1] = LoadTexture("assets/tiles/tile1.png");
  tileTexturesArr[2] = LoadTexture("assets/tiles/tile2.png");
}
