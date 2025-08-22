#ifndef TILE_H
#define TILE_H

#include "raylib.h"
#include "common.h"

Tile createTile();
void loadTileTextures(Texture2D *tileTexturesArr);
void initTileArr(Tile *tileArr);
void drawTile(Tile *tileArr, Texture2D *tileTexturesArr);
void placeTile(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera, User *user);
void deleteTile(Tile *tileArr, Texture2D texture, Camera2D *camera);
void updateTile(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera, User *user);
void drawTileGrid(int size, Tile *tileArr);
void checkInput(Texture2D *tileTexturesArr, User *user);
void loadFile(Tile *tileArr);

#endif
