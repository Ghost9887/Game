#include "ui.h"
#include "exportMap.h"

void drawBottomBar(Texture2D *tileTextureArr){
  int size = 32;
  DrawRectangle(0, SCREENHEIGHT - 100, SCREENWIDTH, SCREENHEIGHT, BLUE);
  Rectangle src = {0, 0, 32, 32};
  for(int i = 1; i <= 20; i++){
    Vector2 pos = {i * size, SCREENHEIGHT - 100};
    DrawTextureRec(tileTextureArr[i], src, pos, WHITE);
  }
}


void drawSaveButton(){
  Rectangle button = {SCREENWIDTH - 100, 10, 80, 50};
  DrawRectangleRec(button, GREEN);
  DrawText(TextFormat("%s", "Save Map"), button.x + 10, button.y + button.height / 2, 10, BLACK);
}

bool checkCollisionWithSaveButton(){
  if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
  Vector2 pos = GetMousePosition();
  Rectangle rec1 = {pos.x, pos.y, 32, 32};
  Rectangle saveButton = {SCREENWIDTH - 100, 10, 80, 50}; 
  if(CheckCollisionRecs(rec1, saveButton)){
    return true;
  }
  
  return false;
  }
}

void callExport(Tile *tileArr){
  if(checkCollisionWithSaveButton()){
    exportMap(tileArr);
    CloseWindow();
  }
}

void updateUI(Texture2D *tileTextureArr, User *user, Tile *tileArr){
  drawBottomBar(tileTextureArr);
  drawSaveButton();
  callExport(tileArr);
}
