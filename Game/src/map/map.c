#include "map.h"
#include "tile.h"
#include "weaponbuy.h"
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
}

void drawMap(Tile *tileArr, Texture2D *tileTexturesArr, Chunk *chunkArr, Camera2D *camera){
  Rectangle cameraView = {
    camera->target.x - SCREENWIDTH / 2,
    camera->target.y - SCREENHEIGHT / 2,
    SCREENWIDTH,
    SCREENHEIGHT
  };
  //DrawRectangleRec(cameraView, RED);
  for(int i = 0; i < 9; i++){
   if(CheckCollisionRecs(cameraView, chunkArr[i].rec)){
      int index = chunkArr[i].startIndex;
      for(int y = 0; y < 74; y++){
        for(int x = 0; x < 74; x++){
          if(tileArr[index].id < 10){
            DrawTexture(tileTexturesArr[tileArr[index].id], tileArr[index].x, tileArr[index].y, WHITE);
          }
          index++;
        }
        index += 222 - chunkArr[i].rec.width / 32;
      } 
    }
  }
}

void spawnObjects(WeaponBuy *weaponBuyArr, Weapon *weaponArr, Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    if(tileArr[i].id >= 10){
      spawnWeaponBuy(weaponBuyArr, &weaponArr[tileArr[i].id - 10], (int)tileArr[i].x, (int)tileArr[i].y);
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
            tileArr[index].id = mapArr[index];
            index++;
        }
    }
}

void loadTileTextures(Texture2D *tileTexturesArr){
  tileTexturesArr[0] = LoadTexture("assets/tiles/white.png");
  tileTexturesArr[1] = LoadTexture("assets/tiles/tile1.png");
  tileTexturesArr[2] = LoadTexture("assets/tiles/tile2.png");

  tileTexturesArr[10] = LoadTexture("assets/weapons/pistol/pistol.png");
  tileTexturesArr[11] = LoadTexture("assets/weapons/ar/ar.png");
  tileTexturesArr[12] = LoadTexture("assets/weapons/rpg/rpg.png");
  tileTexturesArr[13] = LoadTexture("assets/weapons/shotgun/shotgun.png");
  tileTexturesArr[14] = LoadTexture("assets/weapons/smg/smg.png");
  tileTexturesArr[15] = LoadTexture("assets/weapons/rpg/rpg.png");
}
