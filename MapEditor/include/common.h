#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include <stdbool.h>

#define MAXTILES 49284
#define TARGETFPS 60
#define SCREENWIDTH 1200
#define SCREENHEIGHT 900

typedef struct{
  int id;
  int x;
  int y;
  int width;
  int height;
  bool walkable;
  bool active;
  Texture2D texture;
}Tile;

typedef struct{
  int textureId;
}User;

#endif


