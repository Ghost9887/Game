#include "tile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>


Tile createTile(){
  Tile tile;
  tile.id = 0;
  tile.x = 0;
  tile.y = 0;
  tile.width = 32; 
  tile.height = 32;
  tile.walkable = false;
  tile.weaponBuy = false;
  tile.perkBuy = false;
  tile.texture;
  return tile;
}

void initTileArr(Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    tileArr[i] = createTile();
  }
}

void loadTileTextures(Texture2D *tileTexturesArr){
  tileTexturesArr[0] = LoadTexture("assets/tiles/white.png");
  tileTexturesArr[1] = LoadTexture("assets/tiles/tile1.png");
  tileTexturesArr[2] = LoadTexture("assets/tiles/tile2.png");

  //figure out a way to place weaponbuys on top of tiles
  //pistol id = 0 tile id = 10 - 10
  //ar id = 1 tile id = 11 - 10; MAYBE???
  tileTexturesArr[10] = LoadTexture("../Game/assets/weapons/pistol/pistol.png");
  tileTexturesArr[11] = LoadTexture("../Game/assets/weapons/ar/ar.png");
  tileTexturesArr[12] = LoadTexture("../Game/assets/weapons/rpg/rpg.png");
  tileTexturesArr[13] = LoadTexture("../Game/assets/weapons/shotgun/shotgun.png");
  tileTexturesArr[14] = LoadTexture("../Game/assets/weapons/smg/smg.png");
  tileTexturesArr[15] = LoadTexture("../Game/assets/weapons/rpg/rpg.png");


  //perks
  tileTexturesArr[20] = LoadTexture("../Game/assets/perks/health.png");
  tileTexturesArr[21] = LoadTexture("../Game/assets/perks/speed.png");
}

void loadFile(Tile *tileArr) {
    FILE *file = fopen("../Game/assets/map.mp", "r");
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
        int id, walkable, weaponBuy, perkBuy;
        sscanf(token, "%d{%d,%d,%d}", &id, &walkable, &weaponBuy, &perkBuy);
        tileArr[index].id = id;
        tileArr[index].walkable = walkable;
        tileArr[index].weaponBuy = weaponBuy;
        tileArr[index].perkBuy = perkBuy;
        token = strtok(NULL, ";");  
        printf("Parsing index %d: %s\n", index, token);
        index++;
    }

}



void drawTileGrid(int size, Tile *tileArr){
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


void placeTile(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera, User *user){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT)){
    Vector2 pos = GetScreenToWorld2D(GetMousePosition(), *camera);
    Rectangle rec1 = {pos.x, pos.y, 32, 32};
    for(int i = 0; i < MAXTILES; i++){
      Rectangle rec2 = {tileArr[i].x, tileArr[i].y, tileArr[i].width, tileArr[i].height};
      if(CheckCollisionRecs(rec1, rec2)){
        tileArr[i].texture = tileTexturesArr[user->textureId];
        tileArr[i].id = user->textureId;
        if(tileArr[i].id >= 10 && tileArr[i].id <= 19){
          tileArr[i].weaponBuy = true;
        }
        else if(tileArr[i].id >= 20 && tileArr[i].id <= 29){
          tileArr[i].perkBuy = true;
        }
        break;
      }
    }
  } 
}

void checkInput(Texture2D *tileTextureArr, User *user){
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    int size = 32;
    Vector2 pos = GetMousePosition();
      Rectangle rec1 = {pos.x, pos.y, 32, 32};
      for(int i = 1; i <= 30; i++){
        Rectangle rec2 = {i * size, SCREENHEIGHT - 100, tileTextureArr[i].width, tileTextureArr[i].height};
        if(CheckCollisionRecs(rec1, rec2)){
          user->textureId = i;
          break;
        }
      }
  }
}

void drawTile(Tile *tileArr, Texture2D *tileTexturesArr){
  int size = 32;
  for(int i = 0; i < MAXTILES; i++){
    Rectangle rect = {0, 0, (float)tileArr[i].width, (float)tileArr[i].height};
    Vector2 pos = {tileArr[i].x, tileArr[i].y};
    DrawTextureRec(tileTexturesArr[tileArr[i].id], rect, pos, WHITE);
    if(tileArr[i].id > 0){
      DrawText(TextFormat("%d", tileArr[i].id), pos.x + size / 2, pos.y + size / 2, 10, RED);
    }
  }
}

void deleteTile(Tile *tileArr, Texture2D texture, Camera2D *camera){
  if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
    Vector2 pos = GetScreenToWorld2D(GetMousePosition(), *camera);
    Rectangle rec1 = {pos.x, pos.y, 32, 32};
    for(int i = 0; i < MAXTILES; i++){
      Rectangle rec2 = {tileArr[i].x, tileArr[i].y, tileArr[i].width, tileArr[i].height};
      if(CheckCollisionRecs(rec1, rec2)){
        tileArr[i].texture = texture;
        tileArr[i].id = 0;
        tileArr[i].walkable = false;
        tileArr[i].weaponBuy = false;
        tileArr[i].perkBuy = false;
        break;
      }
    }
  }
}

void updateTile(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera, User *user){
  drawTile(tileArr, tileTexturesArr);
  deleteTile(tileArr, tileTexturesArr[0], camera);
  placeTile(tileArr, tileTexturesArr, camera, user);
  checkInput(tileTexturesArr, user);
}
