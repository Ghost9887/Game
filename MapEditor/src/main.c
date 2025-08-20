  
#include "common.h"
#include "mapeditor.h"
#include "tile.h"
#include "ui.h"
#include "user.h"

int main(void){
  InitWindow(SCREENWIDTH, SCREENHEIGHT, "Map Editor");

  Camera2D camera = { 0 };
  camera.zoom = 1.0f;

  int fileArr[MAXTILES];
  loadFile(fileArr); 

  Texture2D tileTexturesArr[MAXTILES];
  loadTileTextures(tileTexturesArr);
  Tile tileArr[MAXTILES];
  initTileArr(tileArr);

  User user;
  user = createUser();

  SetTargetFPS(TARGETFPS);              

  while (!WindowShouldClose()){    // Detect window close button or ESC key
  BeginDrawing();
      ClearBackground(BLACK);
     BeginMode2D(camera);
     mapEditor(tileArr, tileTexturesArr, &camera, &user, fileArr);
    EndMode2D();
    updateUI(tileTexturesArr, &user, tileArr);
  EndDrawing();
  }

  CloseWindow();        // Close window and OpenGL context
  return 0;
}


