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
