#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "common.h"

Tile createTile();
void loadTileTextures(Texture2D *tileTexturesArr);
void initTileArr(Tile *tileArr);
void drawTile(Tile *tileArr);
void placeTile(Tile *tileArr, Texture2D *tileTexturesArr);
void deleteTile(Tile *tileArr, Texture2D texture);
void updateTile(Tile *tileArr, Texture2D *tileTexturesArr);
void drawTileGrid(int size, Tile *tileArr, Texture2D texture);

#endif
