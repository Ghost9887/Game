#ifndef COMMON_H
#define COMMON_H

#include "raylib.h"
#include <stdbool.h>

#define MAXTILES 48000
#define TARGETFPS 60
#define SCREENWIDTH 1200
#define SCREENHEIGHT 900

typedef struct{
  int x;
  int y;
  int width;
  int height;
  bool walkable;
  bool active;
  int equipped; //index of the texture we want
  Texture2D texture;
}Tile;

typedef struct{
  Texture2D equippedTexture;
}User;

#endif


