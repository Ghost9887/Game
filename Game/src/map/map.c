#include "map.h"
#include "tile.h"
#include "weaponbuy.h"
#include "perkBuy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void loadMap(Tile *tileArr) {
    FILE *file = fopen("assets/map.mp", "r");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    char buffer[500000];
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Failed to read file");
        fclose(file);
        return;
    }
    fclose(file);
    char *token = strtok(buffer, ";");  
    int index = 0;
    while (token != NULL && index < MAXTILES) {
        int id, walkable, weaponBuy, weaponId, perkBuy, perkId;
        sscanf(token, "%d{%d,%d{%d},%d{%d}}", &id, &walkable, &weaponBuy, &weaponId, &perkBuy, &perkId);
        tileArr[index].id = id;
        tileArr[index].walkable = walkable;
        tileArr[index].weaponBuy = weaponBuy;
        tileArr[index].weaponId = weaponId;
        tileArr[index].perkBuy = perkBuy;
        tileArr[index].perkId = perkId;
        token = strtok(NULL, ";");  
        index++;
    }
}

void drawGrid(Tile *tileArr, int size){
  int tilesPerRow = 7104 / size;
  int tilesPerColumn = 7104 / size;
  int index = 0;
  for (int y = 0; y < tilesPerColumn; y++) {
    for (int x = 0; x < tilesPerRow; x++) {
      Vector2 pos = { x * size, y * size };
      Rectangle rec = { 0, 0, 32, 32 }; 
      tileArr[index].x = pos.x;
      tileArr[index].y = pos.y;
      index++;
    }
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

void spawnObjects(WeaponBuy *weaponBuyArr, Weapon *weaponArr, PerkBuy *perkBuyArr, Perk *perkArr, Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    printf("In spawn objects\n");
    if(tileArr[i].weaponBuy){
      spawnWeaponBuy(weaponBuyArr, &weaponArr[tileArr[i].weaponId], (int)tileArr[i].x, (int)tileArr[i].y);
    }
    else if(tileArr[i].perkBuy){

      spawnPerkBuy(perkBuyArr, &perkArr[tileArr[i].perkId], (int)tileArr[i].x, (int)tileArr[i].y);
    }
    printf("spawned\n");
  }
}


void initTileArr(Tile *tileArr) {
  for(int i = 0; i < MAXTILES; i++){
    tileArr[i] = createTile();
  }
}

void loadTileTextures(Texture2D *tileTexturesArr){
  tileTexturesArr[0] = LoadTexture("assets/tiles/white.png");
  tileTexturesArr[1] = LoadTexture("assets/tiles/tile1.png");
  tileTexturesArr[2] = LoadTexture("assets/tiles/tile2.png");

  /*
  tileTexturesArr[10] = LoadTexture("assets/weapons/pistol/pistol.png");
  tileTexturesArr[11] = LoadTexture("assets/weapons/ar/ar.png");
  tileTexturesArr[12] = LoadTexture("assets/weapons/rpg/rpg.png");
  tileTexturesArr[13] = LoadTexture("assets/weapons/shotgun/shotgun.png");
  tileTexturesArr[14] = LoadTexture("assets/weapons/smg/smg.png");
  tileTexturesArr[15] = LoadTexture("assets/weapons/rpg/rpg.png");

  tileTexturesArr[20] = LoadTexture("assets/perks/health.png");
  tileTexturesArr[21] = LoadTexture("assets/perks/speed.png");
  */
}
