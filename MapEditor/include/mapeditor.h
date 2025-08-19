#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "raylib.h"
#include "common.h"

void mapEditor(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D camera);
void mouseZoom(Camera2D camera);

#endif
