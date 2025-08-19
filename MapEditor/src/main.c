  
#include "common.h"
#include "mapeditor.h"
#include "tile.h"
int main(void){
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Map Editor");

  Camera2D camera = { 0 };
  camera.zoom = 1.0f;

  Texture2D tileTexturesArr[MAXTILES];
  loadTileTextures(tileTexturesArr);
  Tile tileArr[MAXTILES];
  initTileArr(tileArr);

  SetTargetFPS(TARGETFPS);              

  while (!WindowShouldClose()){    // Detect window close button or ESC key
  BeginDrawing();
      ClearBackground(BLACK);
     BeginMode2D(camera);
     mapEditor(tileArr, tileTexturesArr, &camera);
    EndMode2D();
  EndDrawing();
  }

  CloseWindow();        // Close window and OpenGL context
  return 0;
}


