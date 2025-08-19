  
#include "common.h"
#include "mapeditor.h"
#include "tile.h"
int main(void){
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "raylib [core] example - basic window");

  Texture2D tileTexturesArr[MAXTILES];
  loadTileTextures(tileTexturesArr);
  Tile tileArr[MAXTILES];
  initTileArr(tileArr);

  SetTargetFPS(TARGETFPS);              
  while (!WindowShouldClose()){    // Detect window close button or ESC key
  BeginDrawing();
    ClearBackground(RAYWHITE);
    mapEditor(tileArr, tileTexturesArr);
  EndDrawing();
  }
  CloseWindow();        // Close window and OpenGL context
  return 0;
}


