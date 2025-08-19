#include "tile.h"

Tile createTile(){
  Tile tile;
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
  tileTexturesArr[0] = LoadTexture("assets/tiles/tile1.png");
  tileTexturesArr[1] = LoadTexture("assets/tiles/tile2.png");
  tileTexturesArr[2] = LoadTexture("assets/tiles/white.png");
}

void drawTileGrid(int size, Tile *tileArr, Texture2D texture){
    int tilesPerRow = SCREENWIDTH / size;
    int tilesPerColumn = SCREENHEIGHT / size;
    int index = 0;
    for (int y = 0; y < tilesPerColumn; y++) {
        for (int x = 0; x < tilesPerRow; x++) {
            Vector2 pos = { x * size, y * size };
            Rectangle rec = { 0, 0, 32, 32 }; // Adjust if using a tileset
            tileArr[index].x = pos.x;
            tileArr[index].y = pos.y;
            tileArr[index].active = true;
            DrawTextureRec(texture, rec, pos, WHITE);
            index++;
        }
    }
}

void placeTile(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera){
  if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
    Vector2 pos = GetScreenToWorld2D(GetMousePosition(), *camera);
    Rectangle rec1 = {pos.x, pos.y, 32, 32};
    for(int i = 0; i < MAXTILES; i++){
      if(tileArr[i].active){
        Rectangle rec2 = {tileArr[i].x, tileArr[i].y, tileArr[i].width, tileArr[i].height};
        if(CheckCollisionRecs(rec1, rec2)){
          tileArr[i].texture = tileTexturesArr[1];
          break;
        }
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
          break;
        }
      }
    }
  }

}

void updateTile(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera){
  drawTileGrid(32, tileArr, tileTexturesArr[2]);
  placeTile(tileArr, tileTexturesArr, camera);
  drawTile(tileArr);
  deleteTile(tileArr, tileTexturesArr[2], camera);
}
