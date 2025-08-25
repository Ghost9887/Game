#include "tile.h"


Tile createTile(){
  Tile tile;
  tile.id = 0;
  tile.x = 0;
  tile.y = 0;
  tile.width = 32;
  tile.height = 32;
  tile.walkable = false;
  tile.weaponBuy = false;
  tile.weaponId = -1;
  tile.perkBuy = false; 
  tile.perkId = -1;
  tile.texture;
  return tile;
}
