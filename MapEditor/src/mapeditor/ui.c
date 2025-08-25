#include "ui.h"
#include "exportMap.h"

void drawBottomBar(Texture2D *tileTextureArr) {
    const int tileSize = 32;
    const int barHeight = 150;
    const int rows = 5;
    const int columns = 40;
    const int startIndex = 1;
    DrawRectangle(0, SCREENHEIGHT - barHeight, SCREENWIDTH, barHeight, BLUE);
    Rectangle src = { 0, 0, tileSize, tileSize };
    int index = startIndex;
    for (int row = 0; row < rows; row++) {
        int yPos = SCREENHEIGHT - barHeight + row * tileSize;
        for (int col = 0; col < columns; col++) {
            int xPos = col * tileSize;
            Vector2 pos = { (float)xPos, (float)yPos };
            DrawTextureRec(tileTextureArr[index], src, pos, WHITE);
            index++;
        }
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
