#include "mapeditor.h"
#include "tile.h"

void mapEditor(Tile *tileArr, Texture2D *tileTextureArr){
  int size = 32;
  int width = 1;
  int columns = SCREENWIDTH / size;
  int rows = SCREENHEIGHT / size;
  updateTile(tileArr, tileTextureArr);
}


