#include "tile.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool mapLoaded = false;

Tile createTile(){
  Tile tile;
  tile.id = 0;
  tile.x = 0;
  tile.y = 0;
  tile.width = 32; 
  tile.height = 32;
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
}

void loadFile(int *fileArr) {
    FILE *file = fopen("../Game/assets/map.mp", "r");
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
        fileArr[index] = atoi(comma);
        comma = strtok(NULL, ",");
        index++;
    }
}

void drawTileGrid(int size, Tile *tileArr, Texture2D *tileTexturesArr, int *fileArr){
    int tilesPerRow = 7104 / size;
    int tilesPerColumn = 7104 / size;
    int index = 0;
    for (int y = 0; y < tilesPerColumn; y++) {
        for (int x = 0; x < tilesPerRow; x++) {
            Vector2 pos = { x * size, y * size };
            Rectangle rec = { 0, 0, 32, 32 }; 
            tileArr[index].x = pos.x;
            tileArr[index].y = pos.y;
            if(!mapLoaded){
              tileArr[index].id = fileArr[index];
            }
            DrawTextureRec(tileTexturesArr[tileArr[index].id], rec, pos, WHITE);
            if(tileArr[index].id > 0){
              DrawText(TextFormat("%d", tileArr[index].id), pos.x + size / 2, pos.y + size / 2, 10, RED);
            }
            index++;
        }
    }
    mapLoaded = true;
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
      for(int i = 1; i <= 20; i++){
        Rectangle rec2 = {i * size, SCREENHEIGHT - 100, tileTextureArr[i].width, tileTextureArr[i].height};
        if(CheckCollisionRecs(rec1, rec2)){
          user->textureId = i;
          break;
        }
      }
  }
}

void drawTile(Tile *tileArr){
  for(int i = 0; i < MAXTILES; i++){
    Rectangle rect = {0, 0, (float)tileArr[i].width, (float)tileArr[i].height};
    Vector2 pos = {tileArr[i].x, tileArr[i].y};
    DrawTextureRec(tileArr[i].texture, rect, pos, WHITE);
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
        break;
      }
    }
  }
}

void updateTile(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera, User *user, int *fileArr){
  drawTile(tileArr);
  deleteTile(tileArr, tileTexturesArr[0], camera);
  placeTile(tileArr, tileTexturesArr, camera, user);
  checkInput(tileTexturesArr, user);
  drawTileGrid(32, tileArr, tileTexturesArr, fileArr);
}
