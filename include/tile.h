#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "common.h"

Tile createTile();
void loadTileTextures(Texture2D *tileTexturesArr);
void initTileArr(Tile *tileArr);
void drawTile(Tile *tileArr);
void placeTile(Tile *tileArr, Texture2D *tileTexturesArr);
void deleteTile(int index);
void updateTile(Tile *tileArr, Texture2D *tileTexturesArr);

#endif
