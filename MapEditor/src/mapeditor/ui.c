#include "ui.h"


void drawBottomBar(Texture2D *tileTextureArr){
  int size = 32;
  DrawRectangle(0, SCREENHEIGHT - 100, SCREENWIDTH, SCREENHEIGHT, BLUE);
  Rectangle src = {0, 0, 32, 32};
  for(int i = 0; i < 2; i++){
    Vector2 pos = {i * size, SCREENHEIGHT - 100};
    DrawTextureRec(tileTextureArr[i], src, pos, WHITE);
  }
}

void checkInput(Texture2D *tileTextureArr, User *user){
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
    int size = 32;
    Vector2 pos = GetMousePosition();
      Rectangle rec1 = {pos.x, pos.y, 32, 32};
      for(int i = 0; i < 2; i++){
        Rectangle rec2 = {i * size, SCREENHEIGHT - 100, tileTextureArr[i].width, tileTextureArr[i].height};
        if(CheckCollisionRecs(rec1, rec2)){
          user->equippedTexture = tileTextureArr[i];
          break;
        }
      }
  }
}

void updateUI(Texture2D *tileTextureArr, User *user){
  drawBottomBar(tileTextureArr);
  checkInput(tileTextureArr, user);
}
