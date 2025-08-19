#include "mapeditor.h"
#include "tile.h"

void mapEditor(Tile *tileArr, Texture2D *tileTextureArr){
  int size = 32;
  int width = 1;
  int columns = SCREENWIDTH / size;
  int rows = SCREENHEIGHT / size;
  drawGrid(columns, rows, size, width);   
  updateTile(tileArr, tileTextureArr);
}

void drawGrid(int columns, int rows, int size, int width){
  for(int i = 1; i <= columns; i++){
    DrawLine(i * size, 0, i * size, SCREENHEIGHT, BLACK);
  }
  for(int i = 1; i <= rows; i++){
    DrawLine(0, i * size, SCREENWIDTH, i * size, BLACK);
  }
}

