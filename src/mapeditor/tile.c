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
}

void placeTile(Tile *tileArr, Texture2D *tileTexturesArr){
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    Vector2 pos = GetMousePosition();
    for(int i = 0; i < MAXTILES; i++){
      if(!tileArr[i].active){
        tileArr[i].x = (int)pos.x;
        tileArr[i].y = (int)pos.y;
        tileArr[i].active = true;
        tileArr[i].texture = tileTexturesArr[0];
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

void deleteTile(int index){

}

void updateTile(Tile *tileArr, Texture2D *tileTexturesArr){
  placeTile(tileArr, tileTexturesArr);
  drawTile(tileArr);
}

