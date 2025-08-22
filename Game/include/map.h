#ifndef MAP_H
#define MAP_H

#include "raylib.h"
#include "common.h"

void loadMap(Tile *tileArr);
void initTileArr(Tile *tileArr);
void drawGrid(Tile *tileArr, int size);
void drawMap(Tile *tileArr, Texture2D *tileTextureArr, Chunk *chunkArr, Camera2D *camera);
void loadTileTextures(Texture2D *tileTexturesArr);
void spawnObjects(WeaponBuy *weaponBuyArr, Weapon *weaponArr, Tile *tileArr);

#endif
