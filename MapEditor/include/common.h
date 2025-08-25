#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include <stdbool.h>

#define MAXTILES 49284
#define TARGETFPS 60
#define SCREENWIDTH 1200
#define SCREENHEIGHT 900
#define MAXWEAPONBUYS 50
#define SOLIDBLOCKSSTART 10
#define WEAPONSTART 20 //index in the texture array of where the weaponbuys start
#define PERKSTART 30 //same thing here

typedef struct{
  int id;
  int x;
  int y;
  int width;
  int height;
  bool walkable;
  bool weaponBuy;
  int weaponId;
  bool perkBuy;
  int perkId;
  Texture2D texture;
}Tile;

typedef struct{
  int textureId;
}User;

#endif


