#ifndef MAPEDITOR_H
#define MAPEDITOR_H

#include "raylib.h"
#include "common.h"

void mapEditor(Tile *tileArr, Texture2D *tileTexturesArr, Camera2D *camera, User *user, int *fileArr);
void cameraZoom(Camera2D *camera);

#endif
