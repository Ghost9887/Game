#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "raylib.h"
#include "common.h"

void freezeTime();
void mapEditor(Tile *tileArr, Texture2D *tileTexturesArr);
void drawGrid(int columns, int rows, int size, int width);

#endif
