#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "common.h"

void loadMap(int *mapArr);
void initTileArr(Tile *tileArr, int *mapArr);
void drawMap(Tile *tileArr, Texture2D *tileTextureArr, Chunk *chunkArr, Camera2D *camera);
void loadTileTextures(Texture2D *tileTexturesArr);

#endif
