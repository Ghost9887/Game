#include "tile.h"

Tile createTile(){
  Tile tile;
  tile.id = 0;
  tile.x = 0;
  tile.y = 0;
  tile.width = 32; 
  tile.height = 32;
  tile.walkable = false;
  tile.active = false;
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
}

void drawTileGrid(int size, Tile *tileArr, Texture2D *tileTexturesArr){
    int tilesPerRow = 7000 / size;
    int tilesPerColumn = 7000 / size;
    int index = 0;
    for (int y = 0; y < tilesPerColumn; y++) {
        for (int x = 0; x < tilesPerRow; x++) {
            Vector2 pos = { x * size, y * size };
            Rectangle rec = { 0, 0, 32, 32 }; 
            tileArr[index].x = pos.x;
            tileArr[index].y = pos.y;
            tileArr[index].active = true;
            DrawTextureRec(tileTexturesArr[tileArr[index].id], rec, pos, WHITE);
            if(tileArr[index].id > 0){
              DrawText(TextFormat("%d", tileArr[index].id), pos.x + size / 2, pos.y + size / 2, 10, RED);
            }
            index++;
        }
    }
}

void placeTile(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera, User *user){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT) && !IsKeyDown(KEY_LEFT_SHIFT)){
    Vector2 pos = GetScreenToWorld2D(GetMousePosition(), *camera);
    Rectangle rec1 = {pos.x, pos.y, 32, 32};
    for(int i = 0; i < MAXTILES; i++){
      if(tileArr[i].active){
        Rectangle rec2 = {tileArr[i].x, tileArr[i].y, tileArr[i].width, tileArr[i].height};
        if(CheckCollisionRecs(rec1, rec2)){
          tileArr[i].texture = tileTexturesArr[user->textureId];
          tileArr[i].id = user->textureId;
          break;
        }
      }
    }
    
  } 
}


void checkInput(Texture2D *tileTextureArr, User *user){
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    int size = 32;
    Vector2 pos = GetMousePosition();
      Rectangle rec1 = {pos.x, pos.y, 32, 32};
      for(int i = 1; i < 3; i++){
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
    if(tileArr[i].active){
      Rectangle rect = {0, 0, (float)tileArr[i].width, (float)tileArr[i].height};
      Vector2 pos = {tileArr[i].x, tileArr[i].y};
      DrawTextureRec(tileArr[i].texture, rect, pos, WHITE);
    }
  }
}

void deleteTile(Tile *tileArr, Texture2D texture, Camera2D *camera){
  if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT)){
    Vector2 pos = GetScreenToWorld2D(GetMousePosition(), *camera);
    Rectangle rec1 = {pos.x, pos.y, 32, 32};
    for(int i = 0; i < MAXTILES; i++){
      if(tileArr[i].active){
        Rectangle rec2 = {tileArr[i].x, tileArr[i].y, tileArr[i].width, tileArr[i].height};
        if(CheckCollisionRecs(rec1, rec2)){
          tileArr[i].texture = texture;
          tileArr[i].id = 0;
          break;
        }
      }
    }
  }

}

void updateTile(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera, User *user){
 placeTile(tileArr, tileTexturesArr, camera, user);
  drawTile(tileArr);
  deleteTile(tileArr, tileTexturesArr[0], camera);
  checkInput(tileTexturesArr, user);
  drawTileGrid(32, tileArr, tileTexturesArr);
}
